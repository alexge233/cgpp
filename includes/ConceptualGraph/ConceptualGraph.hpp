#ifndef _CGPP_ConceptualGraph_HPP_
#define _CGPP_ConceptualGraph_HPP_ 
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Conceptual Graph class as described by J.Sowa
 * @class ConceptualGraph
 * @date 15-December-2015
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 */
class ConceptualGraph
{
public:

    /// Empty Constructor
    ConceptualGraph();

    /// Construct using a string @param json - @note guid is randomly generated (uid v4)
    /// @param json must be a valid cgpp json string - else a runtime exception is thrown
    ConceptualGraph(const std::string json);

    /// Copy Constructor - Shallow copy - @note guid is copied
    ConceptualGraph(const ConceptualGraph &);

    /// Identical Graph operator: comparison of Concepts, Relations, Edges by Value and Index
    bool operator==(const ConceptualGraph &) const;

    /// Isomorphic Graph operator: Concept & Relation perumutations are allowed
    /// but Edge Order must be preserved
    bool operator|=(const ConceptualGraph &) const;

    /// Add a new Concept  @note will accept duplicates
    bool add_concept(Concept concept);

    /// Add a new Relation @note will accept duplicates
    bool add_relation(Relation relation);

    /// Add a new Edge (connect Relation to Concept) @note will only create if edge doesn't exist
    bool add_edge(
                    const std::shared_ptr<Relation>, 
                    const std::shared_ptr<Concept>
                 );

    /// Add a new Edge (connect Concept to Relation) @note will only create if edge doesn't exist
    bool add_edge(
                    const std::shared_ptr<Concept>, 
                    const std::shared_ptr<Relation>
                 );

    /// Get Graph's Concepts
    std::vector<Concept> concepts() const;

    /// Get Graph's Relations
    std::vector<Relation> relations() const;

    /// Get All Edges
    std::vector<Edge> edges() const;
    
    /// Get Concepts to which @param Relation has edges to
    std::vector<Concept> has_edges(const Relation &) const;

    /// Get Relations to which of @param Concept has edges to
    std::vector<Relation> has_edges(const Concept &) const;

    /// Jaccard Index for two graph's |V| and |E|, using: 
    ///     `J(G,G') = |G ∩ G'| / (|G|+|G'| - |G ∩ G'|)`
    float jaccard_coeff(const ConceptualGraph &) const;

    /// Sørensen–Dice coefficient for Graphs G and G':
    ///     `S(G,G') = 2 |G ∩ G'| / |G| + |G'|`
    float sorensen_coeff(const ConceptualGraph &) const;

    /// Graph Sparseness: |V| / |E|
    float sparseness() const;

    /// Average path length
    float avg_path_length() const;

    /// Edge search space
    float edge_space() const;
    
    /// Sørensen–Dice coefficient for Graph Nodes V and V':
    ///    `S(V,V') = 2 |V ∩ V'|/|V|+|V'|`
    float node_similarity(const ConceptualGraph &) const;
    
    /// Sørensen–Dice coefficient for Graph Edges E and E':
    ///    `S(E,E') = 2 |E ∩ E'|/|E|+|E'|`
    float edge_similarity(const ConceptualGraph &) const;

    /// Graph Unique ID @note this is a UUID v4
    boost::uuids::uuid guid() const;

    /// Print Graph G' = (V,E) where V = (C,R) on stdout
    void print() const;

    /// Output this graph as JSON well-formatted string
    std::string json() const;

    /// Outpit this graph as a JSON minified string
    std::string minif_json() const;

    /// Serialise graph to a binary file with filename @param file
    void save(const std::string) const;

    /// Deserialise graph from a binary file with filename @param file
    void load(const std::string);

protected:

    friend class boost::serialization::access;

    /// Graph Unique ID
    std::string _guid;
    /// JSON string
    std::string _json;
    /// current concepts
    std::vector<Concept> _concepts;
    /// current relations
    std::vector<Relation> _relations;
    /// current edges: [Relation,Concept] or [Concept,Relation]
    std::vector<Edge> _edges;
    /// Current Proto version
    static constexpr int _version = 1;


    /// parse relation objects from json
    void _parse_relations(rapidjson::Document &);

    /// parse concept objects from json
    void _parse_concepts(rapidjson::Document &);

    /// parse edge from json adjacencies
    void _parse_edges(rapidjson::Document &);

    template <class Archive> 
	void serialize(Archive & ar, const unsigned int)
    {
         ar & _concepts;
		 ar & _relations; 
		 ar & _edges; 
		 ar & _guid;
    }
};
}
#endif
