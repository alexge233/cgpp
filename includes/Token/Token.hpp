#ifndef _CGPP_Token_HPP_
#define _CGPP_Token_HPP_
#pragma once
#include "Includes.hxx"

namespace cgpp
{

/**
 * Class Wrapping around a Token/Word which has a Part-Of-Speech Tag
 * @version 8
 * @date 21-August-2014
 */
class Token
{
  public:


    /// NOTE: cereal requires default constructible or Save/Load methods FIX: Make it private, and give access to cereal only!
    Token ( ) = default;

    /// Defacto constructor
    Token (
            const std::string & value,
            const std::string & tag
          )
    : _value ( value ), _postag ( tag )
    { }


    /// Copy constructor
    Token ( const Token & token )
    : _value ( token._value ), _postag( token._postag)
    { }


    /// Get raw value
    std::string value ( ) const
    {
        if ( !_value.empty() )
            return _value;
        else
            throw std::runtime_error ( "Token value is empty" );
    }


    /// Part of Speech Tag
    std::string tag ( ) const
    {
        return _postag;
    }


    /// Equality operator - Case insensitive
    bool operator== ( const Token & rhs  ) const
    {
        if ( this->_value.empty() || rhs._value.empty() )
            throw std::runtime_error ( "[Token::operator==] empty string" );

        return boost::iequals( this->_value, rhs._value );
    }

    /// Inequality operator - Case insensitive
    bool operator!= ( const Token & rhs ) const
    {
        if ( this->_value.empty() || rhs._value.empty() )
            throw std::runtime_error ( "[Token::operator!=] empty string" );

        return ( boost::iequals( this->_value, rhs._value ) == false ? true : false );
    }

    /// Sorting Operator
    bool operator< ( const Token & rhs ) const
    {
        return this->_value < rhs._value;
    }


  private:

    friend class cereal::access;

    /// Raw string value
    std::string _value;

    /// Part of speech tag
    std::string _postag;


    template <class Archive>
    void serialize ( Archive & archive )
    {
      archive ( _value, _postag );
    }

};

}

#endif 

