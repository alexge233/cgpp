#ifndef _CGPP_Concept_HPP_
#define _CGPP_Concept_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Concept node as described by J. Sowa
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @version 2
 * @date 30-March-2015
 */
class Concept : public Node
{
  public:

    /// Empty Constructor
    Concept ( ) : Node ( ) {}

    /// Construct using a Token only
    Concept ( Token & token ) : Node( token ) {}

    /// Construct using Token and Token Index
    Concept (
              Token & token,
              int index
            )
    :   Node ( token ), _token_index ( index )
    {}

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
    inline int TokenIndex ( ) const
    {
        return _token_index;
    }

  private:

    friend class ConceptualGraph;
    friend class cereal::access;

    /// tokens[i]
    int _token_index = -1;

    
    inline bool isEqual ( const Object &rhs ) const
    {
        return (*this->_token ) == (*static_cast<const Concept &>(rhs)._token)
                && this->_token_index == static_cast<const Concept &>(rhs)._token_index;
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ), _token_index );
    }

};
}
#endif
