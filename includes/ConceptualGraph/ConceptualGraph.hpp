#ifndef _CGPP_ConceptualGraph_HPP_
#define _CGPP_ConceptualGraph_HPP_ 
#pragma once
#include "Includes.hxx"


namespace cgpp {

/**
 * @brief Conceptual Graph class as described by J.Sowa
 * @class ConceptualGraph
 * @version 9
 * @date 12-March-2015
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 */

class ConceptualGraph
{
  public:

    /* Constructors */

    /// Empty Constructor
    ConceptualGraph ( );

    /// Construct using a string @param json - @note guid is randomly generated (uid v4)
    ConceptualGraph ( const std::string json );

    /// Copy Constructor - Shallow copy - @note guid is copied
    ConceptualGraph ( const ConceptualGraph & rhs );

    /// Cloning Constructor, see implementation for details
    ConceptualGraph Clone ( ) const;


    /* Operators */

    /// Identical Graph operator - @note comparison of Concepts, Relations, Edges by Value and Index
    bool operator== ( const ConceptualGraph & rhs ) const;

    /// Isomorphic Graph operator - @note Concept & Relation perumutations are allowed - but Edge Order must be preserved
    bool operator|= ( const ConceptualGraph & rhs ) const;

    /// TODO: Similarity Graph operator - @count min-max node & edge similarity as a metric
    float operator%= ( const ConceptualGraph & rhs ) const;


    /* Setters */

    /// Add a new Concept  @note will accept duplicates
    bool AddConcept ( const std::shared_ptr<Concept> );

    /// Add a new Relation @note will accept duplicates
    bool AddRelation ( const std::shared_ptr<Relation> );

    /// Add a new Edge (connect Relation to Concept) @note will only create if edge doesn't exist
    bool AddEdge ( const std::shared_ptr<Relation>, const std::shared_ptr<Concept> );

    /// Add a new Edge (connect Concept to Relation) @note will only create if edge doesn't exist
    bool AddEdge ( const std::shared_ptr<Concept>, const std::shared_ptr<Relation> );


    /* Getters */

    /// Get Graph's Concepts
    std::vector<std::shared_ptr<Concept>> Concepts ( ) const;

    /// Get Graph's Relations
    std::vector<std::shared_ptr<Relation>> Relations ( ) const;

    /// Get All Edges
    std::vector<Edge> Edges ( ) const;

    /// Get Concepts to which @param Relation has edges to
    std::vector<std::shared_ptr<Concept>> Edges ( const std::shared_ptr<Relation> ) const;

    /// Get Relations to which of @param Concept has edges to
    std::vector<std::shared_ptr<Relation>> Edges (const std::shared_ptr<Concept> ) const;


    /* Graph Meta-Metrics */

    /// Edge to Node ratio: |E| / |V|
    float ratioEdgeVertex ( ) const;

    /// Graph Sparseness: |V| / |E|
    float graphSparseness ( ) const;

    /// Average Pathway Score
    float avgPathLength ( ) const;

    /// Branching Factor / Suggraph Ratio
    float sugraphRatio ( ) const;

    /// Edge Permutation State Size
    float edgePermutations ( ) const;

    
    /* Graph Info and (De)Serialisation */

    /// Graph Unique ID @note this is a UUID v4
    boost::uuids::uuid GUID ( ) const;

    /// Output this graph as JSON well-formatted string
    std::string JSON ( ) const;

    /// Outpit this graph as a JSON minified string
    std::string minifiedJSON ( ) const;

    /// print graph on std::out
    void Echo ( );

    /// Serialise graph to a binary file with filename @param file
    void Save ( const std::string ) const;

    /// Deserialise graph from a binary file with filename @param file
    void Load ( const std::string );


  protected:

    friend class cereal::access;

    /// Graph Unique ID
    std::string _guid;

    /// JSON string
    std::string _json;

    /// current concepts
    std::vector<std::shared_ptr<Concept>> _concepts;

    /// current relations
    std::vector<std::shared_ptr<Relation>> _relations;

    /// current edges: [Relation,Concept] or [Concept,Relation]
    std::vector<Edge> _edges;

    /// Current Proto version
    static constexpr int _version = 1;


    /**             @note JSON methods                      */

    /// parse relation objects from json
    void _parseRelations ( rapidjson::Document & );

    /// parse concept objects from json
    void _parseConcepts ( rapidjson::Document & );

    /// parse edge from json adjacencies
    void _parseEdges ( rapidjson::Document & );


    /// (De)Serialisation delegate for cereal library
    template <class Archive> void serialize ( Archive & archive )
    {
         archive( _concepts, _relations, _edges, _guid );
    }

};

}


#endif
