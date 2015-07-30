#ifndef _CGPP_Node_HPP_
#define _CGPP_Node_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp
{

/**
 * @brief Inteface Abstract Base Class, used for Operators
 */
class Object
{
public:
    
    virtual ~Object() {}
    
    bool operator==( const Object & other ) const
    {
        // If the derived types are the same then compare them
        return typeid (*this) == typeid(other) && isEqual ( other );
    }
    
    bool operator!= ( const Object & other ) const
    {
        return typeid (*this) == typeid(other) && !isEqual ( other );
    }

private:
    // A pure virtual function derived classes must implement.
    // Furthermore, this function has a precondition that it will only
    // be called when the 'other' is the same type as the instance
    // invoking the function.
    virtual bool isEqual ( const Object & other ) const = 0;
};

/**
 * @brief Base Node Class supports Node operations in graph
 * @version 4
 * @date 31-March-2015
 */
class Node : public Object
{
public:

    Node ( )
    {
        _json_id = boost::uuids::random_generator()();
    }

    Node ( Token token )
    {
        _token = std::make_shared<Token>( token );
        _json_id = boost::uuids::random_generator()();
    }

    Node ( const Node & node )
    {
        assert( node._token );
        this->_token = std::make_shared<Token>( *node._token );
        this->_json_id = node._json_id;
    }

    Node & operator= ( const Node & node ) 
    {
        assert( node._token );
        if ( this != &node ) // prevent self-assignment
        {
            this->_token = std::make_shared<Token>( *node._token );
            this->_json_id = node._json_id;
        }
        return *this;
    }

    virtual ~Node ( ){ }

    inline std::shared_ptr<Token> asToken ( ) const
    {
        assert( this->_token ); 
        return std::make_shared<Token>( (*this->_token) );
    }
    
    inline bool operator< ( const Node & rhs ) const
    {
        assert( this->_token && rhs._token );
        return this->_token < rhs._token;
    }
    
    virtual int TokenIndex ( ) const
    {
        return -1;
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

    /// Equality operator for Node (@see class Object)
    /// The equality depends upon Token Value only.
    /// The class Object also uses class type equality
    inline virtual bool isEqual ( const Object & rhs ) const
    {
        auto other = static_cast<const Node&>(rhs);
        assert( this->_token && other._token );
        return (*this->_token ) == (*static_cast<const Node&>(rhs)._token);
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive( _token );
    }

};

}

#endif
