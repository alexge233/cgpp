#ifndef _CGPP_ConceptualGraph_HPP_
#define _CGPP_ConceptualGraph_HPP_ 
#pragma once
#include "Includes.hxx"


namespace cgpp
{

/**
 * Conceptual Graph class as described by J.Sowa
 *
 * @version 8
 * @date 29-August-2014
 */

class ConceptualGraph
{
  public:

    /// Empty Constructor
<<<<<<< HEAD
    ConceptualGraph ( ) = default;
=======
    ConceptualGraph ( );
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed

    /// Construct using a string @param json - @note guid is randomly generated (uid v4)
    ConceptualGraph ( const std::string json );

    /// Copy Constructor - Shallow copy - @note guid is copied
    ConceptualGraph ( const ConceptualGraph & rhs );

    /// Copy Constructor - Deep Clone - @note deep copy all members
    ConceptualGraph Clone ( ) const;

<<<<<<< HEAD
    /// Generate a new Random GUID
    void GenerateGUID ( );

=======
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed

    /**             @note Graph Operations              */

    /// Equality operator - @note isomorphic similarity comparison (concepts,relations,edges)
    bool operator== ( const ConceptualGraph & rhs ) const;

    /// Add a new Concept  @note will accept duplicates
    bool AddConcept ( const std::shared_ptr<Concept> );

    /// Add a new Relation @note will accept duplicates
    bool AddRelation ( const std::shared_ptr<Relation> );

    /// Add a new Edge (connect Relation to Concept) @note will only create if edge doesn't exist
    bool AddEdge ( const std::shared_ptr<Relation>, const std::shared_ptr<Concept> );

    /// Add a new Edge (connect Concept to Relation) @note will only create if edge doesn't exist
    bool AddEdge ( const std::shared_ptr<Concept>, const std::shared_ptr<Relation> );

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


    /**             @note Various Helper methods          */

    /// Graph Unique ID @note this is a UUID v4
    boost::uuids::uuid GUID ( ) const;

    /// Output this graph as JSON
    std::string JSON ( ) const;

    /// print graph on std::out
    void Echo ( );

    /// Serialise graph to a binary file with filename @param file
    void Save ( const std::string ) const;

    /// Deserialise graph from a binary file with filename @param file
    void Load ( const std::string );


  protected:

    friend class cereal::access;

    /// Graph Unique ID
<<<<<<< HEAD
    std::string _guid;
=======
    boost::uuids::uuid _guid;
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed

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
<<<<<<< HEAD
         archive( _concepts, _relations, _edges, _guid );
=======
         archive( _concepts, _relations, _edges );
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed
    }

};

}


#endif
