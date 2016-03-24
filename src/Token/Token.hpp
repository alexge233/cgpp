#ifndef _CGPP_Token_HPP_
#define _CGPP_Token_HPP_
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Class Wrapping around a Token/Word which has a Part-Of-Speech Tag
 * @author Alex Giokas <a.gkiokas@warwick.ac.uk>
 * @date 15-December-2015
 */
class Token
{
public:
 
	/// Default empty constructor	
    Token() = default;
    
    /// Defacto constructor
    Token(
            const std::string & value,
            const std::string & tag
         )
    : _value(value),_postag(tag)
    {}

	/// Copy constructor
    Token(const Token & token)
    {
		_value = token._value;
		_postag = token._postag;
	}

	/// Assignment
    Token & operator=(const Token & token)
    {
        if (this != &token) {
            this->_value = token._value;
            this->_postag = token._postag;
        }
        return *this;
    }

    /// Get raw value
    std::string value() const
    {
        return _value;    
    }

    /// Part of Speech Tag
    std::string tag() const
    {
        return _postag;
    }

    /// Get Token value by to a std::string
    operator std::string() const
    {
        return _value;
    }

    /// Equality operator - Case insensitive
    bool operator==(const Token & rhs) const
    {
        return strcasecmp(this->_value.c_str(), rhs._value.c_str()) 
               == 0 ? true : false;
    }

    /// Inequality operator - Case insensitive
    bool operator!=(const Token & rhs) const
    {
        return strcasecmp(this->_value.c_str(), rhs._value.c_str()) 
               != 0 ? true : false;
    }

    /// Sorting Operator
    bool operator<(const Token & rhs) const
    {
        return this->_value < rhs._value;
    }

protected:

    friend class boost::serialization::access;

    std::string _value;
    std::string _postag;

    template <class Archive> 
	void serialize(Archive & ar, const unsigned int)
    {
		ar & _value;
	   	ar & _postag;
    }
};
}
#endif 
