#include "ConceptualGraph.hpp"

namespace cgpp
{

std::string ConceptualGraph::JSON ( ) const
{
    /*
     * NOTE: adding \n\r so that json will appear readable to humans :-p
     *       if human readability is not an issue (e.g., nobody will ever read the json) feel free to remove "\n\r" and "\t"
     *
     * WARNING: Save your self a lot of trouble: Validate output: http://jsonlint.com before using it anywhere.
     */

    std::stringstream ss;
    ss << "{\n\r\t\"version\":1,\n\r\t\"guid\":\"" << _guid << "\",\n\r\t\"creator\":null,\n\r\t\"relations\":["; // BUG valgrind reports uninitialised value here

    std::string rstr;
    for ( auto r : _relations )
    {
        rstr += "\n\r\t{\n\r\t\t\"label\":\"" + r->asToken()->value() + "\",\n\r\t\t\"postag\":\"" + r->asToken()->tag() + "\",\n\r";
        rstr += "\t\t\"index\":" + boost::lexical_cast<std::string>( r->TokenIndex() ) + ",\n\r";
        rstr += "\t\t\"id\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( r->asToken()->value() ) ) + "\n\r\t},";
    }
    if ( !rstr.empty() )
    {
        rstr.pop_back();
        ss << rstr;
    }

    ss << "],\n\r\t\"concepts\":[";
    std::string cstr;
    for ( auto c : _concepts )
    {
        cstr += "\n\r\t{\n\r\t\t\"label\":\"" + c->asToken()->value() + "\",\n\r\t\t\"postag\":\"" + c->asToken()->tag() + "\",\n\r";
        cstr += "\t\t\"index\":" + boost::lexical_cast<std::string>( c->TokenIndex() ) + ",\n\r";
        cstr += "\t\t\"id\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( c->asToken()->value() ) ) + "\n\r\t},";
    }
    if ( !cstr.empty() )
    {
        cstr.pop_back();
        ss << cstr;
    }

    ss << "],\n\r\t\"adjacencies\":[";
    std::string estr;
    unsigned int index = 0;
    for ( auto e : _edges )
    {
        estr += "\n\r\t{\n\r\t\t\"nodeFrom\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.from->asToken()->value() ) ) + ",\n\r";
        estr += "\t\t\"nodeTo\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.to->asToken()->value() ) ) + ",\n\r";
        estr += "\t\t\"index\":" + boost::lexical_cast<std::string>( index ) + ",\n\r";

        if ( std::dynamic_pointer_cast<Concept>( e.from ) && std::dynamic_pointer_cast<Relation>( e.to ) )
            estr+= "\t\t\"order\":\"cr\"\n\r";

        else if ( std::dynamic_pointer_cast<Relation>( e.from ) && std::dynamic_pointer_cast<Concept>( e.to ) )
            estr+= "\t\t\"order\":\"rc\"\n\r";

        else
            throw std::runtime_error ( "ConceptualGraph cannnot create JSON adjacancies, unknown edge order" );

        estr+= "\n\r\t},";
        index++;
    }
    if ( !estr.empty() )
    {
        estr.pop_back();
        ss << estr;
    }

    ss << "]\n\r}\n\r";
    return ss.str();
}


std::string ConceptualGraph::minifiedJSON ( ) const
{
    std::stringstream ss;
    ss << "{\"version\":1,\"guid\":\"" << _guid << "\",\"creator\":null,\"relations\":["; // BUG valgrind reports uninitialised value here

    std::string rstr;
    for ( auto r : _relations )
    {
        rstr += "{\"label\":\"" + r->asToken()->value() + "\",\"postag\":\"" + r->asToken()->tag() + "\",";
        rstr += "\"index\":" + boost::lexical_cast<std::string>( r->TokenIndex() ) + ",";
        rstr += "\"id\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( r->asToken()->value() ) ) + "},";
    }
    if ( !rstr.empty() )
    {
        rstr.pop_back();
        ss << rstr;
    }

    ss << "],\"concepts\":[";
    std::string cstr;
    for ( auto c : _concepts )
    {
        cstr += "{\"label\":\"" + c->asToken()->value() + "\",\"postag\":\"" + c->asToken()->tag() + "\",";
        cstr += "\"index\":" + boost::lexical_cast<std::string>( c->TokenIndex() ) + ",";
        cstr += "\"id\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( c->asToken()->value() ) ) + "},";
    }
    if ( !cstr.empty() )
    {
        cstr.pop_back();
        ss << cstr;
    }

    ss << "],\"adjacencies\":[";
    std::string estr;
    unsigned int index = 0;
    for ( auto e : _edges )
    {
        estr += "{\"nodeFrom\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.from->asToken()->value() ) ) + ",";
        estr += "\"nodeTo\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.to->asToken()->value() ) ) + ",";
        estr += "\"index\":" + boost::lexical_cast<std::string>( index ) + ","; // BUG: Not what I want - I need an index respective to the origination nodeFrom - not global

        if ( std::dynamic_pointer_cast<Concept>( e.from ) && std::dynamic_pointer_cast<Relation>( e.to ) )
            estr+= "\"order\":\"cr\"";

        else if ( std::dynamic_pointer_cast<Relation>( e.from ) && std::dynamic_pointer_cast<Concept>( e.to ) )
            estr+= "\"order\":\"rc\"";

        else
            throw std::runtime_error ( "ConceptualGraph cannnot create JSON adjacancies, unknown edge order" );

        estr+= "},";
        index++;
    }
    if ( !estr.empty() )
    {
        estr.pop_back();
        ss << estr;
    }

    ss << "]}";
    return ss.str();
}

//      PROTECTED METHODS



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
                auto label = std::string( data[i]["label"].GetString() );

                if ( label.empty() )
                    throw std::runtime_error ("ConceptualGraph JSON concept obj has empty label, or couldn't cast it into a string, in json: " + _json );

                int index = boost::lexical_cast<int>( data[i]["index"].GetString() );

                auto postag = std::string( data[i]["postag"].GetString() );

                // Token w/t label and POS Tag
                Token token = Token( label, postag );

                if ( auto concept = std::make_shared<Concept>( token, index ) )
                {
                    // get JSON id - used for edge creation
                    concept->_json_id = boost::lexical_cast<std::size_t>( data[i]["id"].GetString() );

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
                 data[i].HasMember( "index" ) )
            {
                auto label = std::string( data[i]["label"].GetString() );

                if ( label.empty() )
                    throw std::runtime_error ("ConceptualGraph JSON relation obj has empty label, or couldn't cast it into a string, in json: " + _json );

                int index = boost::lexical_cast<int>( data[i]["index"].GetString() );

                auto postag = std::string( data[i]["postag"].GetString() );

                // Token w/t label and POS Tag
                Token token = Token( label, postag );

                // Create Relation
                if ( auto relation = std::make_shared<Relation>( token, index ) )
                {
                    // get JSON id - used for edge creation
                    relation->_json_id = boost::lexical_cast<std::size_t>( data[i]["id"].GetString() );

                    // Add
                    _relations.push_back ( relation );
                }
            }
            else
                throw std::runtime_error ( "ConceptualGraph JSON relation obj missing a required member" );
        }
    }
    else
        throw std::runtime_error ( "ConceptualGraph JSON relations obj is not an array" );
}



void ConceptualGraph::_parseEdges ( rapidjson::Document & doc )
{
    // JSON adjacencies
    auto & adj = doc["adjacencies"];

    // Iterate adjacencies
    if ( adj.IsArray() )
    {
        for ( rapidjson::SizeType k = 0; k < adj.Size(); k++ )
        {
            if ( adj[k].HasMember ( "nodeTo" ) &&
            adj[k].HasMember ( "nodeFrom" ) &&
            adj[k].HasMember ( "order" ) )
            {
                // Get json ids
                auto nodeFrom = boost::lexical_cast<std::size_t>( adj[k]["nodeFrom"].GetString() );
                auto nodeTo =  boost::lexical_cast<std::size_t>( adj[k]["nodeTo"].GetString() );

                // string ids for debugging
                auto from_str = boost::lexical_cast<std::string>( adj[k]["nodeFrom"].GetString() );
                auto to_str = boost::lexical_cast<std::string>( adj[k]["nodeTo"].GetString() );

                // Try to find "nodeFrom" in relations and concepts
                auto from_concept = std::find_if ( _concepts.begin(), _concepts.end(), [&]( const std::shared_ptr<Concept> & ptr ) { return nodeFrom == ptr->_json_id; } );
                auto from_relation = std::find_if ( _relations.begin(), _relations.end(), [&]( const std::shared_ptr<Relation> & ptr ){ return nodeFrom == ptr->_json_id; } );

                // Try to find "nodeTo" in relations and concepts
                auto to_concept = std::find_if ( _concepts.begin(), _concepts.end(), [&]( const std::shared_ptr<Concept> & ptr ){ return nodeTo == ptr->_json_id; } );
                auto to_relation = std::find_if ( _relations.begin(), _relations.end(), [&]( const std::shared_ptr<Relation> & ptr ){ return nodeTo == ptr->_json_id; } );

                // [Concept, Relation]
                if ( from_concept != _concepts.end() && to_relation != _relations.end() )
                    AddEdge ( *from_concept, *to_relation );

                // [Relation, Concept]
                else if ( from_relation != _relations.end() && to_concept != _concepts.end() )
                    AddEdge ( *from_relation, *to_concept );

                else if ( from_relation != _relations.end() && to_concept == _concepts.end() )
                    throw std::runtime_error ( "ConceptualGraph cannot find `nodeTo ` Concept: " + to_str +  " for `nodeFrom` Relation: " + from_str + " in json " + _json );

                else if ( from_concept != _concepts.end() && to_relation ==  _relations.end() )
                    throw std::runtime_error ( "ConceptualGraph cannot find `nodeTo` Relation: " + to_str +  " for `nodeFrom` Concept: " + from_str + " in json " + _json );

                else if ( from_concept == _concepts.end() && from_relation ==  _relations.end() )
                    throw std::runtime_error ( "ConceptualGraph cannot find `nodeFrom` Node: " + from_str + " in json " + _json );

                else if ( to_concept ==  _concepts.end() && to_relation ==  _relations.end() )
                    throw std::runtime_error ( "ConceptualGraph cannot find `nodeTo` Node: " + to_str + " in json " + _json );

            }
            else
                throw std::runtime_error ( "ConceptualGraph JSON adjacency member missing" );
        }
    }
    else
      throw std::runtime_error ( "ConceptualGraph JSON relation adjacencies not an array" );
}


}
