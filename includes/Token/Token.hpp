#ifndef _CGPP_Token_HPP_
#define _CGPP_Token_HPP_
#pragma once
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Class Wrapping around a Token/Word which has a Part-Of-Speech Tag
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @version 9
 * @date 30-March-2014
 */
class Token
{
  public:
      
    ///Default empty constructor
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
    inline
    std::string value ( ) const
    {
        if ( _value.empty() )
            throw std::runtime_error ( "Token value is empty" );
        
        return _value;    
    }

    /// Part of Speech Tag
    inline
    std::string tag ( ) const
    {
        if ( _postag.empty() )
            throw std::runtime_error ( "Token POS tag is empty" );
        
        return _postag;
    }

    /// Equality operator - Case insensitive
    inline
    bool operator== ( const Token & rhs  ) const
    {
        if ( this->_value.empty() || rhs._value.empty() )
            throw std::runtime_error ( "Token::operator== empty string" );

        //return boost::iequals( this->_value, rhs._value );
        return ( strcasecmp( this->_value.c_str(), rhs._value.c_str() ) == 0 ? true : false );
    }

    /// Inequality operator - Case insensitive
    inline
    bool operator!= ( const Token & rhs ) const
    {
        if ( this->_value.empty() || rhs._value.empty() )
            throw std::runtime_error ( "[Token::operator!=] empty string" );

        //return ( boost::iequals( this->_value, rhs._value ) == false ? true : false );
        return ( strcasecmp( this->_value.c_str(), rhs._value.c_str() ) != 0 ? true : false );
    }

    /// Sorting Operator
    inline
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

