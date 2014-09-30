#ifndef _CGPP_Concept_HPP_
#define _CGPP_Concept_HPP_
#pragma once
#include "Includes.hxx"

namespace cgpp
{

/**
 * Concept node as described by J. Sowa
 *
 * @version 1
 * @date 8-August-2014
 */

class Concept : public Node
{
  public:

    /// Empty Constructor
    Concept ( ) : Node ( )
    { }

    /// Construct using a Token only
    Concept ( Token & token ) : Node( token )
    { }

    /// Construct using Token and Token Index
    Concept (
              Token & token,
              int index
            )
    :   Node ( token ), _token_index ( index )
    { }

    /// Construct using another node
    Concept ( const Concept & rhs ) 
    : Node( rhs )
    {
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }

    /// Needed by Virtual inheritence
    ~Concept ( ) = default;

    /// Cloner : Deep copy - TEST
    std::shared_ptr<Concept> Clone ( ) const
    {
        return std::make_shared<Concept>( *this );
    }


    /// Concept's Token index
    int TokenIndex ( ) const
    {
        return _token_index;
    }


    /// Equality Operator
    bool operator== ( const Concept & rhs ) const
    {
        return *this->_token == *rhs._token &&
                this->_token_index == rhs._token_index;
    }


    /// Sorting operator
    bool operator< ( const Concept & rhs ) const
    {
        return this->_token < rhs._token;
    }


  private:

    friend class ConceptualGraph;
    friend class cereal::access;

    /// tokens[i]
    int _token_index = -1;

    /// json id
    std::size_t _json_id = -1;


    template <class Archive> void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ), _token_index );
    }

};

}
#endif
