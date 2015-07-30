#ifndef _CGPP_Concept_HPP_
#define _CGPP_Concept_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Concept node as described by J. Sowa
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @version 8
 * @date 29-July-2015
 */
class Concept : public Node
{
public:

    Concept ( ) : Node ( ) {}

    /// Construct with Token
    Concept ( Token & token ) : Node( token ) {}

    /// Construct using Token and Token Index
    Concept (
              Token & token,
              int index
            )
    : Node ( token ), _token_index ( index )
    {}

    Concept ( const Concept & rhs ) : Node( rhs )
    {
        assert( rhs._token );
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }

    Concept & operator= ( const Concept & rhs )
    {
        assert( rhs._token );
        if (this != &rhs )
        {
            Node::operator= ( rhs );
            this->_token_index = rhs._token_index;
        }
        return *this;
    }

    bool operator< ( const Concept & rhs )
    {
        assert( rhs._token );
        return (*this->_token) < (*rhs._token);
    }

    ~Concept ( ) = default;

    /// Clone: Deep copy
    std::shared_ptr<Concept> Clone ( ) const
    {
        return std::make_shared<Concept>( *this );
    }

    inline int TokenIndex ( ) const
    {
        return _token_index;
    }

private:

    friend class ConceptualGraph;
    friend class cereal::access;

    int _token_index = -1;
    
    inline bool isEqual ( const Object &rhs ) const
    {
        auto other = static_cast<const Concept &>(rhs);
        assert( this->_token && other._token );
        return (*this->_token ) == (*other._token) && (this->_token_index == other._token_index);
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ), _token_index );
    }

};
}
#endif
