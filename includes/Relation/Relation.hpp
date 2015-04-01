#ifndef _CGPP_Relation_HPP_
#define _CGPP_Relation_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Relation as defined by J. Sowa describes relational nodes
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @version 7
 * @date 30-March-2015
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

    /// Relation Equality Operator
    inline bool operator== ( const Relation & rhs ) const
    {
        return *this->_token == *rhs._token &&
                this->_token_index == rhs._token_index;
    }

    /// Get Token Index
    inline int TokenIndex ( ) const
    {
        return _token_index;
    }


  private:

    friend class ConceptualGraph;
    friend class cereal::access;


    /// tokens[i]
    int _token_index = -1;

    template <class Archive> void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ), _token_index );
    }


};
}
#endif

