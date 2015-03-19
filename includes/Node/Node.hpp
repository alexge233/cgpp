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
    Node ( )
    {
        _json_id = boost::uuids::random_generator()();
    }

    /// Construct with Token
    Node ( Token token )
    {
        _token = std::make_shared<Token>( token );
        _json_id = boost::uuids::random_generator()();
    }

    /// Copy Constructor
    Node ( const Node & node )
    {
        this->_token = node._token;
        this->_json_id = node._json_id;
    }

    /// Empty Dtor
    virtual ~Node ( ){ }

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

    /// Inequality operator
    virtual bool operator!= ( const Node & rhs ) const
    {
        return (*this->_token ) != (*rhs._token);
    }

    boost::uuids::uuid UUID( ) const
    {
        return _json_id;
    }

  protected:

    friend class cereal::access;

    /// Token
    std::shared_ptr<Token> _token;

    /// json id
    boost::uuids::uuid _json_id;

    /**
     * Position of Node within a Graph's List
     * e.g. if G = {n1, n2, n3} the number signifying the position
     * WARNING THIS IS DEPRECATED
     * DANGER: However, if I remove it, I will void all my previous serialised files!
     */
    int _node_position = -1;


    template <class Archive> void serialize ( Archive & archive )
    {
      archive( _token, _node_position );
    }

};

}

#endif
