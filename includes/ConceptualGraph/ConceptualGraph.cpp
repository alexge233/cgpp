#include "ConceptualGraph.hpp"

// WARNING: Register Concept & Relations HERE, else they will be unknown when serialised, and throw an exception!
CEREAL_REGISTER_TYPE(cgpp::Concept);
CEREAL_REGISTER_TYPE(cgpp::Relation);

namespace cgpp
{

int constexpr ConceptualGraph::_version;


ConceptualGraph::ConceptualGraph ( )
{
    _guid = boost::uuids::random_generator()();
}


ConceptualGraph::ConceptualGraph ( const ConceptualGraph & rhs )
{
    // Copy GUID - WARNING: I used to generate a new one at each copy operation
    this->_guid = rhs._guid;

    // Copy Concepts, Relations, Edges
    this->_concepts = rhs._concepts;
    this->_relations = rhs._relations;
    this->_edges = rhs._edges;
}


ConceptualGraph::ConceptualGraph ( const std::string json )
{
    rapidjson::Document doc;
    const char * txt = json.c_str();
    doc.Parse<0>( txt );

    if ( doc.IsObject() )
    {
        // Check JSON has all needed members
        if ( doc.HasMember( "version" ) && 
             doc.HasMember( "guid" ) && 
             doc.HasMember( "creator" ) &&
             doc.HasMember( "relations") &&
             doc.HasMember( "concepts") &&
             doc.HasMember( "adjacencies") )
        {
            if ( !doc["version"].IsInt() )
                throw std::runtime_error ( "ConceptualGraph version member not an int" );

            auto version = boost::lexical_cast<int>( doc["version"].GetInt() );

            if ( ConceptualGraph::_version == version )
            {
                if ( !doc["guid"].IsString() )
                    throw std::runtime_error ( "ConceptualGraph guid member not a string" );

                // check that uuid is correctly formated (v4 UUID) NOTE: below regex will only accept v4 UUID
                std::string uuid = doc["guid"].GetString();
                std::regex expr ( "[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}", std::regex_constants::icase );

                // ATTENTION: only GCC > 4.9 implements std::regex correctly. Clang works ok.

                if ( std::regex_match ( uuid, expr ) )
                    _guid = boost::lexical_cast<boost::uuids::uuid>( uuid );

                else
                    throw std::runtime_error ( "ConceptualGraph invalid UUID" );

                // Parse Concepts first
                _parseConcepts ( doc );

                // Then parse Relations
                _parseRelations ( doc );

                // Finally, parse Edges (adjacencies)
                _parseEdges ( doc );
            }
            else
                throw std::runtime_error ( "ConceptualGraph JSON: wrong proto version" );
        }
        else
            throw std::runtime_error ( "ConceptualGraph JSON: missing member" );
    }
    else
        throw std::runtime_error ( "ConceptualGraph JSON: not a valid object" ) ;
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
        // Need a predicate, std::equal will compare pointers address, override by using the operator of the actual objects
        concepts = std::equal ( this->_concepts.begin(), this->_concepts.end(), rhs._concepts.begin(), c_pred );
    }

    if ( this->_relations.size() == rhs._relations.size() )
    {
        // Need a predicate, std::equal will compare pointers address, override by using the operator of the actual objects
        relations = std::equal ( this->_relations.begin(), this->_relations.end(), rhs._relations.begin(), r_pred );
    }

    if ( this->_edges.size() == rhs._edges.size() )
    {
        // Don't need a predicate, this is a vector of objects, default operator should suffice
        edges = std::equal ( this->_edges.begin(), this->_edges.end(), rhs._edges.begin() );
    }

    return (concepts && relations && edges);
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


bool ConceptualGraph::AddConcept ( std::shared_ptr<Concept> node )
{
    if ( node )
    {
		if ( std::find_if ( _concepts.begin(), _concepts.end(), [&]( const std::shared_ptr<Concept> & rhs ){ return *node == *rhs; }) 
             == _concepts.end() )
        {
            _concepts.push_back( node );
            node->SetPosition ( std::addressof( _concepts.back() ) - std::addressof( _concepts[0] ) );
            return true;
        }
        return false;
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddConcept null param" );
}


bool ConceptualGraph::AddRelation ( std::shared_ptr<Relation> node )
{
    if ( node )
    {
		if ( std::find_if ( _relations.begin(), _relations.end(),[&]( const std::shared_ptr<Relation> & rhs ){ return *node == *rhs; }) 
            == _relations.end() )
        {
            _relations.push_back( node );
            node->SetPosition ( std::addressof( _relations.back() ) - std::addressof( _relations[0] ) );
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
		/*
         * WARNING: Searching by Pointer Comparisong - Find if both Nodes exist in our vectors
         *          If nodes do not exist in our graph vectors, we will end up with an Edge with unknown Node ownership.
         */
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
				_edges.push_back( (Edge){ relation, concept } );
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
        /*
         * WARNING: Searching by Pointer Comparisong - Find if both Nodes exist in our vectors
         *          If nodes do not exist in our graph vectors, we will end up with an Edge with unknown Node ownership.
         */
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
				_edges.push_back( (Edge){ concept, relation } );
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
					result.push_back ( concept );

				else
					throw std::runtime_error ( "ConceptualGraph error when iterating Edges of a Relation, it wasnt a Concept" );
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
					result.push_back ( relation );
		
				else
					throw std::runtime_error ( "ConceptualGraph error when iterating Edges of a Concept, it wasnt a Relation" );
			}
		}
    }
    return result;
}


/*
std::vector<std::shared_ptr<Concept>> ConceptualGraph::Concept_difference ( const ConceptualGraph & rhs ) const
{
    std::vector<std::shared_ptr<Concept>> diff;
    for ( const auto concept : this->_concepts )
    {
        // If it doesn't exist in rhs._concepts, add into current diff - comparison takes into account both Token value and Token Index
        if ( std::find_if ( rhs._concepts.begin(), rhs._concepts.end(), [&]( const std::shared_ptr<Concept> & ptr ){ return *ptr == *concept; } )
            == rhs._concepts.end() )
        {
            diff.push_back ( concept );
        }
    }
    return diff;
}


std::vector<std::shared_ptr<Relation>> ConceptualGraph::Relation_difference ( const ConceptualGraph & rhs ) const
{
    std::vector<std::shared_ptr<Relation>> diff;
    for ( const auto relation : this->_relations )
    {
        // If it doesn't exist in rhs._relations, add into current diff - comparison takes into account both Token value and Token Index
        if ( std::find_if ( rhs._relations.begin(), rhs._relations.end(), [&]( const std::shared_ptr<Relation> & ptr ){ return *ptr == *relation; } )
            == rhs._relations.end() )
        {
            diff.push_back ( relation );
        }
    }
    return diff;
}


std::vector<Edge> ConceptualGraph::Edge_difference ( const ConceptualGraph & rhs ) const
{
    std::vector<Edge> diff;
    for ( const auto edge : this->_edges )
    {
        if ( std::find ( rhs._edges.begin(), rhs._edges.end(), edge ) == rhs._edges.end() )
        {
            diff.push_back ( edge );
        }
    }
    return diff;
}


std::vector<std::shared_ptr<Concept>> ConceptualGraph::Concept_equality ( const ConceptualGraph & rhs ) const
{
    std::vector<std::shared_ptr<Concept>> same;
    for ( const auto concept : this->_concepts )
    {
        // If it doesn't exist in rhs._concepts, add into current diff - comparison takes into account both Token value and Token Index
        if ( std::find_if ( rhs._concepts.begin(), rhs._concepts.end(), [&]( const std::shared_ptr<Concept> & ptr ){ return *ptr == *concept; } )
            != rhs._concepts.end() )
        {
            same.push_back ( concept );
        }
    }
    return same;
}


std::vector<std::shared_ptr<Relation>> ConceptualGraph::Relation_equality ( const ConceptualGraph & rhs ) const
{
    std::vector<std::shared_ptr<Relation>> same;
    for ( const auto relation : this->_relations )
    {
        // If it doesn't exist in rhs._relations, add into current diff - comparison takes into account both Token value and Token Index
        if ( std::find_if ( rhs._relations.begin(), rhs._relations.end(), [&]( const std::shared_ptr<Relation> & ptr ){ return *ptr == *relation; } )
            != rhs._relations.end() )
        {
            same.push_back ( relation );
        }
    }
    return same;
}


std::vector<Edge> ConceptualGraph::Edge_equality ( const ConceptualGraph & rhs ) const
{
    std::vector<Edge> same;
    for ( const auto edge : this->_edges )
    {
        if ( std::find ( rhs._edges.begin(), rhs._edges.end(), edge )  != rhs._edges.end() )
        {
            same.push_back ( edge );
        }
    }
    return same;
}
*/

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
    return _guid;
}


} // namespace end