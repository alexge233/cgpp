#ifndef _CGPP_ConceptualGraph_HPP_
#define _CGPP_ConceptualGraph_HPP_ 
#pragma once
#include "Includes.hxx"


namespace cgpp
{

/**
 * Conceptual Graph class as described by J.Sowa
 *
 * @version 7
 * @date 21-August-2014
 */

class ConceptualGraph
{
  public:

    /// Empty Constructor - use directly, used indirectly by cereal
    ConceptualGraph ( );

    /**
     * Construct using JSON string
     * @note guid is randomly generated (uid v4)
     * @note all concepts, relations & edges are contained in graph
     */
    ConceptualGraph ( const std::string json );

    /**
     * Copy Constructor (Deep Copy Everything)
     * @note guid is copied
     * @note all concepts, relations & edges are deep copied
     */
    ConceptualGraph ( const ConceptualGraph & rhs );

    /**
     * Deep Clone Copy Constructor
     * @note every member of the graph will be deep copied
     */
    ConceptualGraph Clone ( ) const;


    /**
     * Equality operator
     * @note isomorphic similarity comparison (concepts,relations,edges)
     */
    bool operator== ( const ConceptualGraph & rhs ) const;


    /**
     * Add a new Concept
     * @note will accept duplicates
     */
    bool AddConcept ( const std::shared_ptr<Concept> );

    /**
     * Add a new Relation
     * @note will accept duplicates
     */
    bool AddRelation ( const std::shared_ptr<Relation> );

    /**
     * Add a new Edge (connect Relation to Concept)
     * @note will only create if edge doesn't exist
     * @return true on edge created
     */
    bool AddEdge ( const std::shared_ptr<Relation>, const std::shared_ptr<Concept> );

    /**
     * Add a new Edge (connect Concept to Relation)
     * @note will only create if edge doesn't exist
     * @return true on edge created
     */
    bool AddEdge ( const std::shared_ptr<Concept>, const std::shared_ptr<Relation> );


    /**
     * Get Graph's Concepts
     * @warning pointers may be shared with other graphs
     */
    std::vector<std::shared_ptr<Concept>> Concepts ( ) const;

    /**
     * Get Graph's Relations
     * @warning pointers may be shared with other graphs
     */
    std::vector<std::shared_ptr<Relation>> Relations ( ) const;

    /**
     * Get All Edges
     * @return a vector of copied Edges with shared Node pointers
     */
    std::vector<Edge> Edges ( ) const;

    /**
     * Get Concepts to which @param Relation has edges to
     * @return a vector of shared Concept pointers
     */
    std::vector<std::shared_ptr<Concept>> Edges ( const std::shared_ptr<Relation> ) const;

    /**
     * Get Relations to which of @param Concept has edges to
     * @return a vector of shared Relation pointers
     */
    std::vector<std::shared_ptr<Relation>> Edges (const std::shared_ptr<Concept> ) const;


    /**
     * Graph Unique ID
     * @note this is a UUID v4
     */
    boost::uuids::uuid GUID ( ) const;

    /// Output this graph as JSON
    std::string JSON ( ) const;

    /// print graph on std::out
    void Echo ( );

    /// Serialise graph to a binary file
    void Save ( const std::string ) const;

    /// Deserialise graph from a binary file
    void Load ( const std::string );


  protected:

    friend class cereal::access;


    /// Graph Unique ID
    boost::uuids::uuid _guid;

    /// current concepts
    std::vector<std::shared_ptr<Concept>> _concepts;

    /// current relations
    std::vector<std::shared_ptr<Relation>> _relations;

    /// current edges: [Relation,Concept] or [Concept,Relation]
    std::vector<Edge> _edges;

    /// Current Proto version
    static constexpr int _version = 1;



    /// parse relation objects from json
    void _parseRelations ( rapidjson::Document & );

    /// parse concept objects from json
    void _parseConcepts ( rapidjson::Document & );

    /// parse edge from json adjacencies
    void _parseEdges ( rapidjson::Document & );


    template <class Archive> void serialize ( Archive & archive )
    {
         archive( _concepts, _relations, _edges );
    }

};

}


#endif
