#include "ConceptualGraph.hpp"
BOOST_CLASS_EXPORT(cgpp::Concept);
BOOST_CLASS_EXPORT(cgpp::Relation);

namespace cgpp
{

int constexpr ConceptualGraph::_version;

ConceptualGraph::ConceptualGraph()
{
	auto uuid = boost::uuids::random_generator()();
	_guid = boost::lexical_cast<std::string>( uuid );
}

ConceptualGraph::ConceptualGraph(const ConceptualGraph & rhs)
{
    // WARNING Generate a new UUID for each Graph Object
    // Is this a BUG or was it a requirement? I can't remember!
    //auto uuid = boost::uuids::random_generator()();
    //this->_guid = boost::lexical_cast<std::string>( uuid );
	this->_guid = rhs._guid;
    this->_concepts = rhs._concepts;
    this->_relations = rhs._relations;
    this->_edges = rhs._edges;
}

bool ConceptualGraph::operator==(const ConceptualGraph & rhs) const
{
    bool concepts = false, relations = false, edges = false;

    if (this->_concepts.size() == rhs._concepts.size())
        concepts = std::equal(this->_concepts.begin(), this->_concepts.end(), 
							  rhs._concepts.begin(), 
                              [](const Concept& lhs, const Concept& rhs)->bool 
                              { return lhs == rhs;});

    if (this->_relations.size() == rhs._relations.size())
        relations = std::equal(this->_relations.begin(), this->_relations.end(),
							   rhs._relations.begin(), 
							   [](const Relation& lhs, const Relation& rhs )->bool 
                               { return lhs == rhs;});

    if (this->_edges.size() == rhs._edges.size())
        edges = std::equal(this->_edges.begin(), this->_edges.end(), rhs._edges.begin());

    return concepts && relations && edges;
}

bool ConceptualGraph::operator|=(const ConceptualGraph & rhs) const
{
    bool concepts = false, relations = false;
	bool edges = true;

    if (this->_concepts.size() == rhs._concepts.size())
    {
        concepts = std::is_permutation(this->_concepts.begin(), 
									   this->_concepts.end(), 
									   rhs._concepts.begin(),
                                       [&](const Concept & item1, 
										   const Concept & item2)->bool
                                        { return item1 == item2;});
    }

    if (this->_relations.size() == rhs._relations.size())
    {
        relations = std::is_permutation(this->_relations.begin(), 
										this->_relations.end(), rhs._relations.begin(),
                                        [&](const Relation & item1, 
											const Relation & item2)->bool
                                         { return item1 == item2;});
    }

    if (this->_edges.size() != rhs._edges.size())
		return false;

	auto my_concepts = this->_concepts;
	auto other_concepts = rhs._concepts;
	for (const auto & mine : my_concepts)
	{
		for (const auto & other : other_concepts)
		{
			if (mine == other)
			{
				const auto mines = this->has_edges(mine);
				const auto othrs = rhs.has_edges(other);

				// Same Edges for This Concept
				if (mines.size() == othrs.size())
				{
					if (!std::equal( mines.begin(), mines.end(), othrs.begin(),
										[&](const Relation& item1, 
											const Relation& item2)->bool
										{return (item1 == item2);})){ return false; }
				}
				else return false;
			}
		}
	}
	// keep local copies of vectors - WHY?
	auto my_relations = this->_relations;
	auto other_relations = rhs._relations;
	for (const auto & mine : my_relations)
	{
		for (const auto & other : other_relations)
		{
			if (mine == other)
			{
				const auto mines = this->has_edges(mine);
				const auto othrs = rhs.has_edges(other);
				if ( mines.size() == othrs.size() )
				{
					if ( !std::equal( mines.begin(), mines.end(), othrs.begin(),
									[&](const Concept& item1, 
										const Concept& item2)->bool
									{return (item1 == item2);})) return false;
				}
				else return false;
			}
		}
	}
    return concepts && relations && edges;
}

bool ConceptualGraph::add_concept(Concept concept)
{
    if (std::find_if(_concepts.begin(), _concepts.end(), 
                    [&](const Concept & rhs)
                    {return concept == rhs;}) == _concepts.end())
    {
        _concepts.push_back(concept);
        return true;
    }
    return false;
}

bool ConceptualGraph::add_relation(Relation relation)
{
    if (std::find_if(_relations.begin(),_relations.end(),
                    [&](const Relation & rhs)
                    {return relation == rhs;}) == _relations.end())
    {
        _relations.push_back(relation);
        return true;
    }
    return false;
}

bool ConceptualGraph::add_edge (
                                const std::shared_ptr<Relation> relation,
                                const std::shared_ptr<Concept> concept
                              )
{
    assert(concept && relation);
    auto c_it = std::find(_concepts.begin(), _concepts.end(), *concept);
    auto r_it = std::find(_relations.begin(), _relations.end(), *relation);

    // Both exist
    if (c_it != _concepts.end() && r_it != _relations.end())
    {
        if (std::find_if(_edges.begin(),_edges.end(),
                         [&]( const Edge & rhs )
                         { return *rhs.from == *relation && *rhs.to == *concept; }) 
						== _edges.end())
        {
            // create new edge: [Relation,Concept]
            Edge edge = { relation, concept };
            _edges.push_back( edge );
            return true;
        }
    }
    // TODO: throw runtime exception
    else
        std::cerr << "Warning AddEdge: Concept or Relation doesn't exist in graph,\n\
		Edge not created" << std::endl;
    return false;
}

bool ConceptualGraph::add_edge (
                                const std::shared_ptr<Concept> concept,
                                const std::shared_ptr<Relation> relation
                              )
{
    assert(concept && relation);
    auto c_it = std::find(_concepts.begin(), _concepts.end(), *concept);
    auto r_it = std::find(_relations.begin(), _relations.end(), *relation);
    // Both exist
    if ( c_it != _concepts.end() && r_it != _relations.end() )
    {
        // Find if edge already exists
        if (std::find_if(_edges.begin(),_edges.end(),
                        [&]( const Edge & rhs )
                        {return *rhs.from == *concept && *rhs.to == *relation;}) 
						== _edges.end())
        {
            // create new edge: [Concept,Relation]
            Edge edge = { concept, relation };
            _edges.push_back( edge );
            return true;
        }
    }
    // TODO: throw runtime exception
    else
        std::cerr << "Warning AddEdge: Concept or Relation doesn't exist in graph,\n\
		Edge not created" << std::endl;
    return false;
}

std::vector<Concept> ConceptualGraph::concepts() const
{
    return _concepts;
}

std::vector<Relation> ConceptualGraph::relations() const
{
    return _relations;
}

std::vector<Edge> ConceptualGraph::edges() const
{
    return _edges;
}

std::vector<Concept> ConceptualGraph::has_edges(const Relation & rhs) const
{ 
    std::vector<Concept> result;
    for ( const auto & edge : _edges)
        if (*edge.from == rhs)
            result.push_back(static_cast<Concept &>(*edge.to));
    return result;
}

std::vector<Relation> ConceptualGraph::has_edges(const Concept & rhs) const
{
    std::vector<Relation> result;
    for (const auto & edge : _edges)
        if (*edge.from == rhs)
            result.push_back(static_cast<Relation &>(*edge.to));
    return result;
}

///
/// Graph Metrics
///

float ConceptualGraph::jaccard_coeff(const ConceptualGraph & rhs) const
{
    unsigned int c_same = 0, r_same = 0;
    for ( const auto this_concept : this->_concepts )
        for ( const auto other_concept : rhs._concepts )
            if ( this_concept == other_concept )
                c_same++;
    for ( const auto this_relation : this->_relations )
        for ( const auto other_relation : rhs._relations )
            if ( this_relation == other_relation )
                r_same++;
    unsigned int e_same = 0;
    for ( const auto this_edge : this->_edges )
        for ( const auto other_edge : rhs._edges )
            if ( this_edge == other_edge )
                e_same++;

    unsigned int c_size = this->_concepts.size()+rhs._concepts.size();
    unsigned int r_size = this->_relations.size()+rhs._relations.size();
    unsigned int e_size = this->_edges.size()+rhs._edges.size();

    // J(C,C') and J(R,R')
    float j_c = (float)c_same / (float)(c_size - c_same);
    float j_r = (float)r_same / (float)(r_size - r_same);

    // TODO: Fix & add weight for each ratio don't divide by two
    // @see `tested` branch on github - it has the correct formula

    // normalise node Jaccard = J(V,V')
    float j_v = (j_c + j_r) / 2.f;

    // J(E,E')
    float j_e = (float)e_same / (float)(e_size - e_same);

    // return normalised Jacard = J(G,G')
    return (j_v + j_e) / 2.f;
}

float ConceptualGraph::sorensen_coeff(const ConceptualGraph & rhs) const
{
    return (node_similarity(rhs) + edge_similarity(rhs)) / 2.f;
}

float ConceptualGraph::sparseness() const
{
    return (float)(_concepts.size() + _relations.size()) 
            / (float)(_edges.size());
}

float ConceptualGraph::avg_path_length() const
{
    std::vector<unsigned int> lengths;
    std::function<void ( unsigned int i, unsigned int len )> lambda;
    lambda = [&]( unsigned int i, unsigned int len )
    {
        for (unsigned int k = i + 1; k < _edges.size(); k++)
        {
            if ((*_edges[i].to) == (*_edges[k].from))
            {
                len++;
                lambda (k, len);
            }
        }
        // If it reaches this bit here, then: (a) there is no path, or (b) search has been exhausted
        lengths.push_back(len);
    };
    // Theres already one edge, therefore set to 1
    for (unsigned int i = 0; i < _edges.size(); i++)
        lambda ( i, 1 );
    // accumulate lengths
    unsigned int acc = 0;
    if (lengths.size() > 0)
    {
        for (const auto i : lengths) acc += i;
        return (float)((float)acc / (float)lengths.size());
    }
    else
        return 0.f;
}

float ConceptualGraph::edge_space() const
{
    return (float)(_concepts.size() * _relations.size());
}

float ConceptualGraph::node_similarity(const ConceptualGraph & rhs) const
{
    //  Count similar and different Nodes (nodes_same, nodes_diff)
    unsigned int same_concepts = 0, same_relations = 0;
    for ( const auto this_concept : this->_concepts )
        for ( const auto other_concept : rhs._concepts )
            if ( this_concept == other_concept )
                same_concepts++;

    for ( const auto this_relation : this->_relations )
        for ( const auto other_relation : rhs._relations )
            if ( this_relation == other_relation )
                same_relations++;

    // node percentage #(same nodes)  / total ( nodes ) 
    float node_prc = (2.f * (float)(same_concepts + same_relations)) / 
                     (float)(this->_concepts.size()+rhs._concepts.size()
                     + this->_relations.size()+rhs._relations.size());

    return node_prc;
}

float ConceptualGraph::edge_similarity(const ConceptualGraph & rhs) const
{
    // Count similar and different Edges (edges_same, edges_diff)
    unsigned int same_edges = 0;
    for ( const auto this_edge : this->_edges )
        for ( const auto other_edge : rhs._edges )
            if ( this_edge == other_edge )
                same_edges++;

    // edge percentage #(same edges) / total ( edges )
    float edge_prc = (2.f * (float)same_edges) / 
                     (float)( this->_edges.size() + rhs._edges.size() );

    return edge_prc;
}

//
// Binary (De)Serialization
// 

void  ConceptualGraph::save( const std::string fname ) const
{
     std::ofstream output ( fname );
     if ( output.is_open() )
     {
		boost::archive::binary_oarchive ar(output);
        ar & _concepts;
	    ar & _relations;
        ar & _edges;
		ar & _guid;
     }
     else 
        throw std::runtime_error("can't open file for saving");;
}

void  ConceptualGraph::load( const std::string fname )
{
    std::ifstream input( fname );
    if ( input.is_open() )
    {
		boost::archive::binary_iarchive ar(input);
        ar & _concepts;
		ar & _relations;
		ar & _edges;
		ar & _guid;
    }
    else
        throw std::runtime_error("can't open file for loading");
}

boost::uuids::uuid ConceptualGraph::guid() const
{
    return boost::lexical_cast<boost::uuids::uuid>(_guid);
}

void ConceptualGraph::print() const
{
   std::cout << "∃(Gₜ): Gₜ(C)={";
   for ( auto con : _concepts )
        std::cout << con.as_token().value() << ",";
   std::cout << "}, Gₜ(R)= {";
   for ( auto rel : _relations )
        std::cout << rel.as_token().value() << ",";
   std::cout << "}, Gₜ(E)= {";
   for ( auto edge : _edges )
        std::cout << "[" << edge.from->as_token().value() << "→" << edge.to->as_token().value() << "],";
   std::cout << "}" << std::endl;
}

// 
// Construct directly from a JSON string
// TODO: REPLACE WITH BOOST !!!
ConceptualGraph::ConceptualGraph(const std::string json)
{
    _json = json;
    rapidjson::Document doc;
    const char * txt = _json.c_str();
    doc.Parse<0>( txt );
    if (doc.IsObject())
    {
        // Check JSON has all needed members
        if ( doc.HasMember("version") &&
             doc.HasMember("guid") &&
             doc.HasMember("creator") &&
             doc.HasMember("relations") &&
             doc.HasMember("concepts") &&
             doc.HasMember("adjacencies") )
        {
            auto version = boost::lexical_cast<int>(doc["version"].GetString());
            if (ConceptualGraph::_version == version)
            {
                // check that uuid is correctly formated (v4 UUID) NOTE: below regex will only accept v4 UUID
                std::string uuid = doc["guid"].GetString();
                static const boost::regex expr("[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}", 
                                                boost::regex_constants::icase);

                if (boost::regex_match(uuid, expr))
                    _guid = uuid;
                else 
                    throw std::runtime_error("ConceptualGraph invalid UUID");

                // Parse Concepts first
                _parse_concepts(doc);
                // Then parse Relations
                _parse_relations(doc);
                // Finally, parse Edges (adjacencies)
                _parse_edges(doc);
            }
            else 
                throw std::runtime_error("ConceptualGraph JSON: wrong proto version");
        }
        else 
            throw std::runtime_error("ConceptualGraph JSON: missing member");
    }
    else 
        throw std::runtime_error("ConceptualGraph JSON: not a valid object") ;
}

//
// Serialisation to JSON
//

std::string ConceptualGraph::json() const
{
    /*
     * NOTE: adding \n\r so that json will appear readable to humans :-p
     * ATTENTION: The id should NOT BE THE MURMUR HASH OF THE VALUE!!! IT SHOULD BE A UNIQUE ID !!!
     */
    std::stringstream ss;
    ss << "{\n\r\t\"version\":1,\n\r\t\"guid\":\"" << _guid << "\",\n\r\t\"creator\":null,\n\r\t\"relations\":["; 
    std::string rstr;
    for ( auto r : _relations )
    {
        rstr += "\n\r\t{\n\r\t\t\"label\":\"" + r.as_token().value() + 
				"\",\n\r\t\t\"postag\":\"" + r.as_token().tag() + "\",\n\r";
        rstr += "\t\t\"index\":" + boost::lexical_cast<std::string>( r.token_index() ) + ",\n\r";
        rstr += "\t\t\"id\":" + boost::lexical_cast<std::string>( r.uuid() ) + "\n\r\t},";
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
        cstr += "\n\r\t{\n\r\t\t\"label\":\"" + c.as_token().value() + 
				"\",\n\r\t\t\"postag\":\"" + c.as_token().tag() + "\",\n\r";
        cstr += "\t\t\"index\":" + boost::lexical_cast<std::string>( c.token_index() ) + ",\n\r";
        cstr += "\t\t\"id\":" + boost::lexical_cast<std::string>( c.uuid() ) + "\n\r\t},";
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
        estr += "\n\r\t{\n\r\t\t\"nodeFrom\":" + boost::lexical_cast<std::string>( e.from->uuid() ) + ",\n\r";
        estr += "\t\t\"nodeTo\":" + boost::lexical_cast<std::string>( e.to->uuid()   ) + ",\n\r";
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

std::string ConceptualGraph::minif_json() const
{
    std::stringstream ss;
    ss << "{\"version\":1,\"guid\":\"" << _guid << "\",\"creator\":null,\"relations\":["; 
    std::string rstr;
    for ( auto r : _relations )
    {
        rstr += "{\"label\":\"" + r.as_token().value() + 
				 "\",\"postag\":\"" + r.as_token().tag() + "\",";
        rstr += "\"index\":" + boost::lexical_cast<std::string>( r.token_index() ) + ",";
        rstr += "\"id\":" + boost::lexical_cast<std::string>( 
							std::hash<std::string>()( r.as_token().value() ) ) + "},";
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
        cstr += "{\"label\":\"" + c.as_token().value() + 
				 "\",\"postag\":\"" + c.as_token().tag() + "\",";
        cstr += "\"index\":" + boost::lexical_cast<std::string>( c.token_index() ) + ",";
        cstr += "\"id\":" + boost::lexical_cast<std::string>( 
							std::hash<std::string>()( c.as_token().value() ) ) + "},";
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
        estr += "{\"nodeFrom\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.from->as_token().value() ) ) + ",";
        estr += "\"nodeTo\":" + boost::lexical_cast<std::string>( std::hash<std::string>()( e.to->as_token().value() ) ) + ",";
        estr += "\"index\":" + boost::lexical_cast<std::string>( index ) + ","; 
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

//
//      JSON Methods for Parsing
//      PROTECTED METHODS
//

void ConceptualGraph::_parse_concepts(rapidjson::Document & doc)
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
                    throw std::runtime_error(
					"JSON concept obj has empty label or can't cast to string: " + _json );

                int index = boost::lexical_cast<int>( data[i]["index"].GetString() );
                auto postag = std::string( data[i]["postag"].GetString() );
                // Token w/t label and POS Tag
                Token token = Token(label, postag);
                Concept concept(token, index);
				std::string uuid = data[i]["id"].GetString();
				static const boost::regex expr( 
						"[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}", 
						boost::regex_constants::icase);
				// get JSON CONCEPT UUID-v4 used for edge creation
				if ( boost::regex_match(uuid, expr) )
					concept._json_id = boost::lexical_cast<boost::uuids::uuid>(uuid);
				else
					throw std::runtime_error ( "Concept invalid ID" );
				// Add to Concepts w/t Token and Token Index
				_concepts.push_back(concept);
            }
            else throw std::runtime_error("JSON concept obj missing a required member" );
        }
    }
    else throw std::runtime_error("JSON concepts obj is not an array" );
}

void ConceptualGraph::_parse_relations(rapidjson::Document & doc)
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
                    throw std::runtime_error(
							"JSON relation obj has empty label or can't cast to string: " 
							+ _json );

                int index = boost::lexical_cast<int>( data[i]["index"].GetString() );
                auto postag = std::string( data[i]["postag"].GetString() );
                // Token w/t label and POS Tag
                Token token = Token(label,postag);
                // Create Relation
                Relation relation(token, index);
				std::string uuid = data[i]["id"].GetString();
				static const boost::regex expr(
						"[0-9a-f]{8}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}", 
						boost::regex_constants::icase );
				// get JSON RELATION UUID-v4 used for edge creation
				if ( boost::regex_match(uuid, expr))
					relation._json_id = boost::lexical_cast<boost::uuids::uuid>(uuid);
				else
					throw std::runtime_error("Relation invalid ID");
				// Add
				_relations.push_back ( relation );
            }
            else throw std::runtime_error("JSON relation obj missing a required member");
        }
    }
    else throw std::runtime_error("JSON relations obj is not an array");
}

void ConceptualGraph::_parse_edges(rapidjson::Document & doc)
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
                auto nodeFrom = boost::lexical_cast<boost::uuids::uuid>( adj[k]["nodeFrom"].GetString() );
                auto nodeTo =  boost::lexical_cast<boost::uuids::uuid>( adj[k]["nodeTo"].GetString() );

                // string ids for debugging
                auto from_str = boost::lexical_cast<std::string>( adj[k]["nodeFrom"].GetString() );
                auto to_str = boost::lexical_cast<std::string>( adj[k]["nodeTo"].GetString() );

                // Try to find "nodeFrom" in relations and concepts
                auto from_concept = std::find_if( _concepts.begin(), 
                                                  _concepts.end(),
                                                  [&](const Concept & rhs)
                                                  {return nodeFrom == rhs._json_id;});

                auto from_relation = std::find_if( _relations.begin(), 
                                                   _relations.end(),
                                                   [&](const Relation & rhs)
                                                   {return nodeFrom == rhs._json_id;});

                // Try to find "nodeTo" in relations and concepts
                auto to_concept = std::find_if(_concepts.begin(),
                                              _concepts.end(),
                                              [&](const Concept & rhs)
                                              {return nodeTo == rhs._json_id;});

                auto to_relation = std::find_if(_relations.begin(),
                                                _relations.end(), 
                                                [&](const Relation & rhs)
                                                {return nodeTo == rhs._json_id;});

                // [Concept, Relation] - Note: from and to are std::shared_ptrs
                if ( from_concept != _concepts.end() && to_relation != _relations.end() )
                    add_edge(std::make_shared<Concept>(*from_concept),
							 std::make_shared<Relation>(*to_relation));

                // [Relation, Concept]
                else if ( from_relation != _relations.end() && to_concept != _concepts.end() )
                    add_edge(std::make_shared<Relation>(*from_relation),
						     std::make_shared<Concept>(*to_concept));

                // Sanity Checks - Missmatching Edges or non-existant nodes
                else if ( from_relation != _relations.end() && to_concept == _concepts.end() )
                    throw std::runtime_error(
							"cannot find `nodeTo ` Concept: " + to_str +  
                            " for `nodeFrom` Relation: " + from_str + " in json " + _json );

                else if ( from_concept != _concepts.end() && to_relation ==  _relations.end() )
                    throw std::runtime_error(
							"cannot find `nodeTo` Relation: " + to_str +  
                            " for `nodeFrom` Concept: " + from_str + " in json " + _json );

                else if ( from_concept == _concepts.end() && from_relation ==  _relations.end() )
                    throw std::runtime_error(
							"cannot find `nodeFrom` Node: " + from_str + " in json " + _json );

                else if ( to_concept ==  _concepts.end() && to_relation ==  _relations.end() )
                    throw std::runtime_error(
							"cannot find `nodeTo` Node: " + to_str + " in json " + _json );
            }
            else throw std::runtime_error("JSON adjacency member missing");
        }
    }
    else throw std::runtime_error("JSON relation adjacencies is not an array");
}

} // namespace end
