#ifndef _CGPP_ConceptualGraph_HPP_
#define _CGPP_ConceptualGraph_HPP_ 
#pragma once
#include "Includes.hxx"

// TODO: Modularise the PARSING methods into smaller private methods. Break it down, and use assertions or tests.

namespace cgpp
{

/**
 * Conceptual Graph class as described by J.Sowa
 *
 * @version 5
 * @date 6-August-2014
 * 
 * NOTE: if I want embeded Graphs, then Concept & ConceptualGraph need a common ABC 
 *       which will provide a basis for an Edge for Relations
 */
class ConceptualGraph
{
  public:
    
    /// Empty Constructor
    ConceptualGraph ( );
    
    /// Construct using JSON string
    ConceptualGraph ( const std::string json );

    /// Copy Constructor (Deep Copy)
    ConceptualGraph ( const ConceptualGraph & rhs );

  

    /// Add a new Concept
    void AddConcept ( const std::shared_ptr<Concept> );

    /// Add a new Relation
    void AddRelation ( const std::shared_ptr<Relation> );
    

    /// Add a new Edge (Connect Relation to Concept)
    bool Connect ( const std::shared_ptr<Relation>, const std::shared_ptr<Concept> );


    /// Equality operator
    bool operator== ( const ConceptualGraph & rhs ) const;



    /// Get Graph's Concepts
    const std::vector<std::shared_ptr<Concept>> & Concepts ( ) const;

    /// Get Graph's Relations
    const std::vector<std::shared_ptr<Relation>> & Relations ( ) const;



    /// Graph Unique ID
    boost::uuids::uuid GUID ( ) const;

    /// Output this graph as JSON
    std::string JSON ( ) const;

    
    /// print graph on std::out
    void Echo ( );


    /// serialise graph to a binary file
    void Save ( const std::string ) const;

    /// deserialise graph from a binary file
    void Load ( const std::string );
 
    
  protected:
    
    /// current concepts
    std::vector<std::shared_ptr<Concept>> _concepts;
    
    /// current relations
    std::vector<std::shared_ptr<Relation>> _relations;

    /// Graph Unique ID
    boost::uuids::uuid _guid;

    /// Current Proto version
    static constexpr int _version = 1;

    
    /// parse relation objects from json
    void _parseRelations ( rapidjson::Document & );

    /// parse concept objects from json
    void _parseConcepts ( rapidjson::Document & );

    
    /* TODO...
    friend class cereal::access;

    template <class Archive> void serialize ( Archive & archive )
    {
         archive( _concepts, _relations );
    }
    */
};


}


#endif
