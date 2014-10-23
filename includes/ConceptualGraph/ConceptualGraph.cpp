#include "ConceptualGraph.hpp"

// WARNING: Register Concept & Relations HERE, else they will be unknown when serialised, and throw an exception!
CEREAL_REGISTER_TYPE(cgpp::Concept);
CEREAL_REGISTER_TYPE(cgpp::Relation);

namespace cgpp
{

int constexpr ConceptualGraph::_version;

ConceptualGraph::ConceptualGraph ()
{
    auto uuid = boost::uuids::random_generator()();         // Vagrind=uninitialised value
    _guid = boost::lexical_cast<std::string>( uuid );
}

ConceptualGraph::ConceptualGraph ( const ConceptualGraph & rhs )
{
    auto uuid = boost::uuids::random_generator()();         // Vagrind=uninitialised value

    // WARNING Generate a new UUID for each Graph Object
    this->_guid = boost::lexical_cast<std::string>( uuid );

    // Copy Concepts, Relations, Edges
    this->_concepts = rhs._concepts;
    this->_relations = rhs._relations;
    this->_edges = rhs._edges;
}


bool ConceptualGraph::operator== ( const ConceptualGraph & rhs ) const
{
    bool concepts = false, relations = false, edges = false;

    auto c_pred = []( const std::shared_ptr<Concept> & lhs,
                      const std::shared_ptr<Concept> & rhs )->bool { return *lhs == *rhs; };

    auto r_pred = []( const std::shared_ptr<Relation> & lhs,
                      const std::shared_ptr<Relation> & rhs )->bool { return *lhs == *rhs; };

    if ( this->_concepts.size() == rhs._concepts.size() )
    {
        concepts = std::equal ( this->_concepts.begin(), this->_concepts.end(), rhs._concepts.begin(), c_pred );
    }

    if ( this->_relations.size() == rhs._relations.size() )
    {
        relations = std::equal ( this->_relations.begin(), this->_relations.end(), rhs._relations.begin(), r_pred );
    }

    if ( this->_edges.size() == rhs._edges.size() )
    {
        edges = std::equal ( this->_edges.begin(), this->_edges.end(), rhs._edges.begin() );
    }

    return concepts && relations && edges;
}

bool ConceptualGraph::operator|= ( const ConceptualGraph & rhs ) const
{
    bool concepts = false, relations = false, edges = false;

    if ( this->_concepts.size() == rhs._concepts.size() )
    {
        concepts = std::is_permutation( this->_concepts.begin(), this->_concepts.end(), rhs._concepts.begin(),
                                        [&]( const std::shared_ptr<Concept> & item1, const std::shared_ptr<Concept> & item2)->bool
                                        { return (*item1 == *item2); } );
    }
    if ( this->_relations.size() == rhs._relations.size() )
    {
        relations = std::is_permutation( this->_relations.begin(), this->_relations.end(), rhs._relations.begin(),
                                         [&]( const std::shared_ptr<Relation> & item1, const std::shared_ptr<Relation> & item2)->bool
                                         { return (*item1 == *item2); } );
    }

    if ( this->_edges.size() == rhs._edges.size() )
    {
        std::vector<bool> edge_res;
        // Keep local copies of vectors
        auto my_concepts = this->_concepts;
        auto other_concepts = rhs._concepts;
        for ( const auto mine : my_concepts )
        {
            for ( const auto other : other_concepts )
            {
                if ( *mine == *other )
                {
                    const auto mines = this->Edges( mine );
                    const auto othrs = rhs.Edges( other );
                    if ( mines.size() == othrs.size() )
                    {
                        if ( !std::equal( mines.begin(), mines.end(), othrs.begin(),
                                            [&]( const std::shared_ptr<Relation> item1, const std::shared_ptr<Relation> item2)->bool
                                            { return (*item1 == *item2); } ) )
                        {
                            edge_res.push_back( false );
                        }
                    }
                    else edge_res.push_back( false );
                }
            }
        }
        // keep local copies of vectors
        auto my_relations = this->_relations;
        auto other_relations = rhs._relations;
        for ( const auto mine : my_relations )
        {
            for ( const auto other : other_relations )
            {
                if ( *mine == *other )
                {
                    const auto mines = this->Edges( mine );
                    const auto othrs = rhs.Edges( other );
                    if ( mines.size() == othrs.size() )
                    {
                        /// std::equal should also take into account the index of the items - TEST
                        if ( !std::equal( mines.begin(), mines.end(), othrs.begin(),
                                        [&]( const std::shared_ptr<Concept> item1, const std::shared_ptr<Concept> item2)->bool
                                        { return *item1 == *item2; } ) )
                        {
                            edge_res.push_back( false );
                        }
                    }
                    else edge_res.push_back( false );
                }
            }
        }

        bool ok = true;
        for ( auto res : edge_res ) { if ( !res ) ok = false; }
        edges = ok;
    }

    return concepts && relations && edges;
}


ConceptualGraph ConceptualGraph::Clone ( ) const
{
    ConceptualGraph copy = ConceptualGraph();
    copy._guid = this->_guid;

    // Concept Cloning lambda
    auto clone_concepts = [](const std::shared_ptr<Concept> & ptr)-> std::shared_ptr<Concept> { return ptr->Clone(); };

    // Relation Cloning lambda
    auto clone_relations = [](const std::shared_ptr<Relation> & ptr)-> std::shared_ptr<Relation> { return ptr->Clone(); };

    // Deep copy Concepts
    std::transform ( this->_concepts.begin(), this->_concepts.end(), std::back_inserter( copy._concepts ), clone_concepts );

    // Deep copy Relations
    std::transform ( this->_relations.begin(), this->_relations.end(), std::back_inserter( copy._relations ), clone_relations );

    // Recreate Edges - by using the old Edges as an example
    for ( auto & edge : this->_edges )
    {
        // Test by downcasting: [Relation,Concept]
        if ( std::dynamic_pointer_cast<Relation>( edge.from ) && std::dynamic_pointer_cast<Concept>( edge.to ) )
        {
            // Find identical nodes using Token/Index comparison NOTE: std::find seems to compare pointer address, so use std::find_if with a lambda
            auto from_it = std::find_if ( copy._relations.begin(), copy._relations.end(), [&]( const std::shared_ptr<Relation> & ptr){ return *edge.from == *ptr;} );
            auto to_it = std::find_if ( copy._concepts.begin(), copy._concepts.end(), [&]( const std::shared_ptr<Concept> & ptr){ return *edge.to == *ptr;} );

            // relation(from) & concept(to) must exist in our own copy by now
            if ( from_it != copy._relations.end() && to_it != copy._concepts.end() )
                copy._edges.push_back( (Edge){ *from_it, *to_it } );

            else
                throw std::runtime_error ( "ConceptualGraph copy constructor did not find copied Concept/Relation for Edge copying (1)" );
        }

        // Test by downcasting: [Concept,Relation]
        else if ( std::dynamic_pointer_cast<Concept>( edge.from ) && std::dynamic_pointer_cast<Relation>( edge.to ) )
        {
            // Find identical nodes using Token/Index comparison NOTE: std::find seems to compare pointer address, so use std::find_if with a lambda
            auto from_it = std::find_if ( copy._concepts.begin(), copy._concepts.end(), [&]( const std::shared_ptr<Concept> & ptr){ return *edge.from == *ptr;} );
            auto to_it = std::find_if ( copy._relations.begin(), copy._relations.end(), [&]( const std::shared_ptr<Relation> & ptr){ return *edge.to == *ptr;} );

            // concept(from) & relation(to) must exist in our own copy by now
            if ( from_it != copy._concepts.end() && to_it != copy._relations.end() )
                copy._edges.push_back( (Edge){ *from_it, *to_it } );

            else
                throw std::runtime_error ( "ConceptualGraph copy constructor did not find copied Concept/Relation for Edge copying (2)" );
        }

        // Anything else is illegal
        else
            throw std::runtime_error ( "ConceptualGraph copy constructor found illegal Edge type" );
    }

    return copy;
}


bool ConceptualGraph::AddConcept ( const std::shared_ptr<Concept> node )
{
    if ( node )
    {
		if ( std::find_if ( _concepts.begin(), _concepts.end(), [&]( const std::shared_ptr<Concept> & rhs ){ return *node == *rhs; }) 
             == _concepts.end() )
        {
            _concepts.push_back( node );
            //node->SetPosition ( std::addressof( _concepts.back() ) - std::addressof( _concepts[0] ) );
            return true;
        }
        return false;
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddConcept null param" );
}


bool ConceptualGraph::AddRelation ( const std::shared_ptr<Relation> node )
{
    if ( node )
    {
        if ( std::find_if ( _relations.begin(), _relations.end(),[&]( const std::shared_ptr<Relation> & rhs ){ return *node == *rhs; }) 
            == _relations.end() )
        {
            _relations.push_back( node );
            //node->SetPosition ( std::addressof( _relations.back() ) - std::addressof( _relations[0] ) );
            return true;
        }
        return false;
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddRelation null param" );
}


bool ConceptualGraph::AddEdge (
                                const std::shared_ptr<Relation> relation,
                                const std::shared_ptr<Concept> concept
                                )
{
    if ( concept && relation )
    {
        auto c_it = std::find ( _concepts.begin(), _concepts.end(), concept );
        auto r_it = std::find ( _relations.begin(), _relations.end(), relation );

        // Both exist
        if ( c_it != _concepts.end() && r_it != _relations.end() )
        {
            // Find if edge already exists - NOTE: I can use Edge::operator== in order to minify this line below
            if ( std::find_if ( _edges.begin(), _edges.end(), [&]( const Edge & rhs ){ return *rhs.from == *relation && *rhs.to == *concept; }) 
                == _edges.end() )
            {
                // create new edge: [Relation,Concept]
                Edge edge = { relation, concept };
                _edges.push_back( edge );
                return true;
            }
        }
        else
            std::cerr << "ConceptualGraph AddEdge: either Concept or Relation doesn't exist in this graph, Edge won't be created" << std::endl;

        return false;
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddEdge null param" );
}


bool ConceptualGraph::AddEdge (
                                const std::shared_ptr<Concept> concept,
                                const std::shared_ptr<Relation> relation
                              )
{
    if ( concept && relation )
    {
        auto c_it = std::find ( _concepts.begin(), _concepts.end(), concept );
        auto r_it = std::find ( _relations.begin(), _relations.end(), relation );

        // Both exist
        if ( c_it != _concepts.end() && r_it != _relations.end() )
        {
            // Find if edge already exists
            if ( std::find_if ( _edges.begin(), _edges.end(), [&]( const Edge & rhs ){ return *rhs.from == *concept && *rhs.to == *relation; })
                == _edges.end() )
            {
                // create new edge: [Concept,Relation]
                Edge edge = { concept, relation };
                _edges.push_back( edge );
                return true;
            }
        }
        else
            std::cerr << "ConceptualGraph AddEdge: either Concept or Relation doesn't exist in this graph, Edge won't be created" << std::endl;

        return false;
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddEdge null param" );
}


std::vector<std::shared_ptr<Concept>> ConceptualGraph::Concepts ( ) const
{
    return _concepts;
}


std::vector<std::shared_ptr<Relation>> ConceptualGraph::Relations ( ) const
{
    return _relations;
}


std::vector<Edge> ConceptualGraph::Edges ( ) const
{
    return _edges;
}


std::vector<std::shared_ptr<Concept>> ConceptualGraph::Edges ( const std::shared_ptr<Relation> rhs ) const
{
    std::vector<std::shared_ptr<Concept>> result;

    for ( const auto & edge : _edges )
    {
        // [from] is a relation, [to] is a concept
        if ( auto lhs = std::dynamic_pointer_cast<Relation>( edge.from ) )
        {
            if ( *lhs == *rhs )
            {
                if ( auto concept = std::dynamic_pointer_cast<Concept>( edge.to ) )
                {
                    result.push_back ( std::make_shared<Concept>( *concept ) );
                }
            }
        }
    }
    return result;
}


std::vector<std::shared_ptr<Relation>> ConceptualGraph::Edges ( const std::shared_ptr<Concept> rhs ) const
{
    std::vector<std::shared_ptr<Relation>> result;

    for ( const auto & edge : _edges )
    {
        // [from] is a concept, [to] is a relation
        if ( auto lhs = std::dynamic_pointer_cast<Concept>( edge.from ) )
        {
            if ( *lhs == *rhs )
            {
                if ( auto relation = std::dynamic_pointer_cast<Relation>( edge.to ) )
                {
                    result.push_back ( std::make_shared<Relation>( *relation ) );
                }
            }
        }
    }
    return result;
}


void  ConceptualGraph::Echo ( )
{
   std::cout << "∃(Gₜ): Gₜ(c)={";
   for ( auto con : _concepts )
        std::cout << con->asToken()->value() << ",";

   std::cout << "}, Gₜ(r)= {";
   for ( auto rel : _relations )
        std::cout << rel->asToken()->value() << ",";

   std::cout << "}, Gₜ(e)= {";
   for ( auto edge : _edges )
        std::cout << "[" << edge.from->asToken()->value() << "→" << edge.to->asToken()->value() << "],";

   std::cout << "}" << std::endl;
}


void  ConceptualGraph::Save ( const std::string fname ) const
{
     std::ofstream output ( fname );

     if ( output.is_open() )
     {
        cereal::BinaryOutputArchive archive( output );
        archive( _concepts, _relations );
        archive( _edges );
     }
     else
        std::cerr << "[ConceptualGraph::Save] Could not open file for saving" << std::endl;
}


void  ConceptualGraph::Load ( const std::string fname )
{
    std::ifstream input( fname );

    if ( input.is_open() )
    {
        cereal::BinaryInputArchive archive ( input );
        archive( _concepts, _relations );
        archive( _edges );
    }
    else
       std::cerr << "[ConceptualGraph::Load] Could not open file for loading" << std::endl;
}


boost::uuids::uuid ConceptualGraph::GUID ( ) const
{
    return boost::lexical_cast<boost::uuids::uuid>( _guid );
}


} // namespace end