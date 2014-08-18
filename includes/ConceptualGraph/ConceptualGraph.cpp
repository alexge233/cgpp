#include "ConceptualGraph.hpp"

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
    
    // Concept Cloning lambda
    auto clone_concepts = [](const std::shared_ptr<Concept> & ptr)-> std::shared_ptr<Concept> { return ptr->Clone(); };
    
    // Relation Cloning lambda
    auto clone_relations = [](const std::shared_ptr<Relation> & ptr)-> std::shared_ptr<Relation>
                             {
                               auto clone = ptr->Clone();
                               // WARNING: Clear Edges - We want clone's Edges to point to cloned concepts not the old concepts
                               clone->_edges.clear();
                               return clone;
                             };

    // Deep copy Concepts
    std::transform ( rhs._concepts.begin(), rhs._concepts.end(), std::back_inserter( this->_concepts ), clone_concepts );

    // Deep copy Relations
    std::transform ( rhs._relations.begin(), rhs._relations.end(), std::back_inserter( this->_relations ), clone_relations );
    
    // Iterate cloned relations - establish correct edges
    for ( auto & relation : this->_relations )
    {
        // Find matching original relation - search by value & node position
        auto it = std::find ( rhs._relations.begin(), rhs._relations.end(), relation);

        // if found
        if ( it != rhs._relations.end() )
        {
            // original relation's edges (subset of the rhs._concepts)
            const auto & original_edges = (*it)->_edges;
            
            // find the cloned match of the original edge
            for ( const auto & edge : original_edges )
            {
                // search by matching value & node position
	            auto match = std::find ( this->_concepts.begin(), this->_concepts.end(), edge );
	            
                // if found - create identical edge
	            if ( match != this->_concepts.end() )
                {
	                relation->_edges.push_back( *match );
                }
	        }
        }
    }

    // NOTE: I could perform some kind of sanity check here to ensure that copy is ok
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
             doc.HasMember( "concepts") )
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
                
		// WARNING: Under Linux, only GCC > 4.9 implements std::regex correctly. Clang works ok.
		
                if ( std::regex_match ( uuid, expr ) )
                    _guid = boost::lexical_cast<boost::uuids::uuid>( uuid );
                else
                    throw std::runtime_error ( "ConceptualGraph invalid UUID" );

                // Always parse Concepts first - so that Relations can create Edges
                _parseConcepts( doc );

                // Then parse Relations, and create Edges whilst doing so
                //_parseRelations( doc ); TODO
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


void ConceptualGraph::_parseRelations ( rapidjson::Document & doc )
{
    auto & data = doc["relations"];

    if ( data.IsArray() )
    {
        // Iterate the relations array - each one is a node object
        for ( rapidjson::SizeType i = 0; i < data.Size(); i++ )
        {
            // Check if relation has members: label, id, postag, index, adjacencies
            if ( data[i].HasMember( "label" ) &&
                 data[i].HasMember( "id" ) &&
                 data[i].HasMember( "postag" ) &&
                 data[i].HasMember( "index" ) &&
                 data[i].HasMember( "adjacencies" ) )
            { 
                if ( !data[i]["label"].IsString() )
                    throw std::runtime_error ( "ConceptualGraph JSON relation label not a string" );
                    
                auto label = std::string( data[i]["label"].GetString() );
                
                if ( label.empty() )
                    throw std::runtime_error ("ConceptualGraph JSON relation obj has empty label" );

                if ( !data[i]["index"].IsInt() )
                    throw std::runtime_error ( "ConceptualGraph JSON relation index not an int" );

                int index = boost::lexical_cast<int>( data[i]["index"].GetInt() );
                    
                if ( !data[i]["postag"].IsString() )
                    throw std::runtime_error ( "ConceptualGraph JSON concept postag not a string" );

                auto postag = std::string( data[i]["postag"].GetString() );
                
                // Token w/t label and POS Tag
                Token token = Token( label, postag );

                // Create Relation
                auto relation = std::make_shared<Relation>( token, index );

                // JSON adjacencies
                auto & adj = data[i]["adjacencies"];

                // Iterate adjacencies
                if ( adj.IsArray() )
                {
                    for ( rapidjson::SizeType k = 0; k < adj.Size(); k++ )
                    {
                        if ( !adj[k]["nodeTo"].IsInt() )
                            throw std::runtime_error ( "ConceptualGraph JSON adjacency id not an int");

                        auto key =  boost::lexical_cast<int>( data[i]["nodeTo"].GetInt() );

                        auto it = std::find_if ( _concepts.begin(), _concepts.end(), [&]( const std::shared_ptr<Concept> & ptr ){ return key == ptr->_json_id; } );
                        
                        // concept found - create edge
                        if ( it != _concepts.end() )
                        {
                            relation->Edge( *it );
                        }
                        else
                            throw std::runtime_error ( "ConceptualGraph JSON adjacency concept not found" );
                    }
                }
            }
            else
                throw std::runtime_error ( "ConceptualGraph JSON relation obj missing a required member" );
        }
    }
    else
        throw std::runtime_error ( "ConceptualGraph JSON relations obj is not an array" );
}


void ConceptualGraph::_parseConcepts ( rapidjson::Document & doc )
{
    auto & data = doc["concepts"];

    if ( data.IsArray() )
    {
        // Iterate the concepts array - each one is a node object
        for ( rapidjson::SizeType i = 0; i < data.Size(); i++ )
        {
            // Check if concept has members: label, id, postag, index, data
            if ( data[i].HasMember( "label" ) &&
                 data[i].HasMember( "id" ) &&
                 data[i].HasMember( "postag" ) &&
                 data[i].HasMember( "index" ) )
            {   
                if ( !data[i]["label"].IsString() )
                    throw std::runtime_error ( "ConceptualGraph JSON concept label not a string" );
                    
                auto label = std::string( data[i]["label"].GetString() );
                
                if ( label.empty() )
                    throw std::runtime_error ("ConceptualGraph JSON concept obj has empty label" );
                                
                if ( !data[i]["index"].IsInt() )
                    throw std::runtime_error ( "ConceptualGraph JSON concept index not an int" );
                
                int index = boost::lexical_cast<int>( data[i]["index"].GetInt() );
                    
                if ( !data[i]["postag"].IsString() )
                    throw std::runtime_error ( "ConceptualGraph JSON concept postag not a string" );

                auto postag = std::string( data[i]["postag"].GetString() );
                
                // Token w/t label and POS Tag
                Token token = Token( label, postag );

                if ( auto concept = std::make_shared<Concept>( token, index ) )
                {
                    // get JSON id - used for edge creation
                    concept->_json_id = boost::lexical_cast<int>( data[i]["id"].GetString() );

                    // Add to Concepts w/t Token and Token Index
                    _concepts.push_back ( concept );
                }
                else
                    throw std::runtime_error ( "ConceptualGraph JSON concept could not be constructed" );
            }
            else
                throw std::runtime_error ( "ConceptualGraph JSON concept obj missing a required member" );
        }
    }
    else
        throw std::runtime_error ( "ConceptualGraph JSON concepts obj is not an array" );
}


bool ConceptualGraph::operator== ( const ConceptualGraph & rhs ) const
{
    // TODO: Return Isomorphic Equality
    return false;
}


const std::vector<std::shared_ptr<Concept>> & ConceptualGraph::Concepts ( ) const
{
    return _concepts;
}


const std::vector<std::shared_ptr<Relation>> &  ConceptualGraph::Relations ( ) const
{
    return _relations;
}


std::string ConceptualGraph::JSON ( ) const
{
    std::string out;
    
    // TODO: produce a valid JSON string from this graph

    return out;
}


void  ConceptualGraph::AddConcept ( std::shared_ptr<Concept> node )
{
    if ( node )
    {
        _concepts.push_back( node );
        node->SetPosition ( std::addressof( _concepts.back() ) - std::addressof( _concepts[0] ) );
    }
    else 
        throw std::runtime_error ( "ConceptualGraph AddConcept null param" );
}


void  ConceptualGraph::AddRelation ( std::shared_ptr<Relation> node )
{
    if ( node )
    {
        // DANGER: Adding by pointer comparison may allow duplicates - since a clone operation will create a new address
        auto it = std::find_if ( _relations.begin(), _relations.end(),
                                [&]( const std::shared_ptr<Relation> r ) 
                                { return r == node; });

        if ( it != _relations.end() )
        {
            *it = node;
        }
        else
        {
            _relations.push_back( node );
            node->SetPosition ( std::addressof( _relations.back() ) - std::addressof( _relations[0] ) );
        }
    }
    else
        throw std::runtime_error ( "ConceptualGraph AddRelation null param" );
}


bool  ConceptualGraph::Connect (
                                 std::shared_ptr<Relation> relation,
                                 std::shared_ptr<Concept> concept
                               )
{
    if ( relation && concept )
    {
        /*
            DANGER: Assuming that both nodes must exist as pointers in our memory space is troublesome.
            
            TODO: If they do not exist, add them - if they exist, create an Edge.
        */

        auto c_it = std::find_if( _concepts.begin(), _concepts.end(),
                                 [&]( const std::shared_ptr<Concept> & c )->bool
                                 { return c == concept; });

        auto r_it = std::find_if( _relations.begin(), _relations.end(),
                                 [&]( const std::shared_ptr<Relation> & r )->bool
                                 { return r == relation; });

        if ( c_it != _concepts.end() && r_it != _relations.end() )
            return (*r_it)->Edge( *c_it );

        if ( c_it == _concepts.end() )
            std::cerr << "[ConceptGraph::Connect] concept ptr not found" << std::endl;

        if ( r_it == _relations.end() )
            std::cerr << "[ConceptGraph::Connect] relation ptr not found" << std::endl;

        return false;
    }
    else 
        throw std::runtime_error ("[ConceptGraph::Connect] null param" );
}


void  ConceptualGraph::Echo ( )
{
   std::cout << "[ConceptualGraph] ∃(G) - G(c)={";
   for ( auto con : _concepts )
        std::cout << con->asToken()->value() << ",";

   std::cout << "}, G(r)= {";
   for ( auto rel : _relations )
        std::cout << rel->asToken()->value() << ",";

   std::cout << "}, G(e)= {";
   for ( auto rel : _relations )
       for ( auto con : rel->Edges() )
            std::cout << "[" << rel->asToken()->value() << "→" << con->asToken()->value() << "],";

   std::cout << "}" << std::endl;
}


void  ConceptualGraph::Save ( const std::string fname ) const
{
     std::ofstream output ( fname );

     if ( output.is_open() )
     {
        cereal::BinaryOutputArchive archive( output );
        archive( _concepts );
        archive( _relations );
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
        archive( _concepts );
        archive( _relations );
    }
    else
       std::cerr << "[ConceptualGraph::Load] Could not open file for loading" << std::endl;
}



}

