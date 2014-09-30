#ifndef _CGPP_Node_HPP_
#define _CGPP_Node_HPP_ 
#pragma once
#include "Includes.hxx"

namespace cgpp
{

/**
 * Base class node supports Node operations in graph
 * @version 3
 * @date 8-August-2014
 */
class Node
{
  public:
    
    
    /// Empty Constructor - Avoid using
    Node ( ) = default;
    
    /// Construct with Token
    Node ( Token token )
    {
        _token = std::make_shared<Token>( token );
    }

    /// Copy Constructor
    Node ( const Node & node )
    {
        this->_token = node._token;
    }

    /// Empty Dtor
    virtual ~Node ( ){ }

    
    /// Node Position in a list
    int Position ( ) const
    {
        return _node_position;
    }

    /// Get Node's Token
    std::shared_ptr<Token> asToken ( ) const
    { 
        return std::make_shared<Token>( (*this->_token) );
    }

    /// Equality operator
    virtual bool operator== ( const Node & rhs ) const
    {
        return (*this->_token ) == (*rhs._token);
    }
    
    /// Set Node position (WARNING Should remove)
    void SetPosition ( int pos )
    {
        _node_position = pos;
    }
    
    
  protected:
   
    friend class cereal::access;
    
    /// Token
    std::shared_ptr<Token> _token;
    
    /**
     * Position of Node within a Graph's List
     * e.g. if G = {n1, n2, n3} the number signifying the position
     */
    int _node_position = -1;
    
    
    template <class Archive> void serialize ( Archive & archive )
    {
      archive( _token, _node_position );
    }
    
    
};

}

#endif
