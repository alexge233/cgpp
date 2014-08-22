#ifndef _CGPP_Relation_HPP_
#define _CGPP_Relation_HPP_
#pragma once
#include "Includes.hxx"

namespace cgpp
{

/**
 * Relation as defined by J. Sowa describes relational nodes
 *
 * @version 6
 * @date 8-August-2014
 */

class Relation : public Node
{
  public:
    
    
    /// Empty Constructor - Avoid using
    Relation ( ) = default;

    /// Construct with Token
    Relation ( Token & token ) : Node( token )
    { }

    /// Construct with Token & Token Index
    Relation (
                Token & token,
                int index
             )
    : Node ( token ), _token_index ( index )
    { }

    /// Construct using another relation
    Relation ( const Relation & rhs ) : Node( rhs )
    {
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }
    
    /// Poly Destructor
    ~Relation ( ) = default;

    /// Clone: Deep copy
    std::shared_ptr<Relation> Clone ( ) const
    {
        return std::make_shared<Relation>( * this );
    }

    /// Equality Operator
    bool operator== ( const Relation & rhs ) const
    {
        return (*this->_token) ==  (*rhs._token);
    }

    /// Get Token Index
    int TokenIndex ( ) const
    {
        return _token_index;
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

