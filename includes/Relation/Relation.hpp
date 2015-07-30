#ifndef _CGPP_Relation_HPP_
#define _CGPP_Relation_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Relation as defined by J. Sowa describes relational nodes
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @version 8
 * @date 29-July-2015
 */
class Relation : public Node
{
public:

    Relation () : Node () {}

    /// Construct with Token
    Relation ( Token & token ) : Node( token ) {}

    /// Construct with Token & Token Index
    Relation (
                Token & token,
                int index
             )
    : Node ( token ), _token_index ( index )
    {}

    Relation ( const Relation & rhs ) : Node( rhs )
    {
        assert( rhs._token );
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }
    
    Relation & operator= ( const Relation & rhs )
    {
        assert( rhs._token );
        if (this != &rhs )
        {
            Node::operator= ( rhs );
            this->_token_index = rhs._token_index;
        }
        return *this;
    }

    bool operator< ( const Relation & rhs ) const
    {
        assert( rhs._token );
        return ( *this->_token ) < ( *rhs._token );
    }
    
    ~Relation ( ) = default;

    std::shared_ptr<Relation> Clone ( ) const
    {
        return std::make_shared<Relation>( * this );
    }

    inline int TokenIndex ( ) const
    {
        return _token_index;
    }


private:

    friend class ConceptualGraph;
    friend class cereal::access;
    int _token_index = -1;
        
    inline bool isEqual ( const Object & rhs ) const
    {
        auto other = static_cast<const Relation &>(rhs); 
        return (*this->_token ) == (*other._token) && (this->_token_index == other._token_index);
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ), _token_index );
    }


};
}
#endif
