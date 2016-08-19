#ifndef _CGPP_Node_HPP_
#define _CGPP_Node_HPP_
#include "Includes.hxx"
namespace cgpp
{
/// @brief Inteface Abstract Base Class, used for Operators
class Object
{
public:
    
    virtual ~Object() {}
    
    bool operator==(const Object & rhs) const
    {
        // If the derived types are the same then compare them
        return typeid(*this) == typeid(rhs) && is_equal(rhs);
    }
    
    bool operator!=(const Object & rhs) const
    {
		// The exact oposite
        return typeid(*this) == typeid(rhs) && !is_equal(rhs);
    }

private:
	// pure virtual used by all inheriting classes for comparison
    virtual bool is_equal(const Object &) const = 0;
};

/**
 * @brief Base Node Class supports Node operations in graph
 * @date 15-December-2015
 */
class Node : public Object
{
public:

	/// Empty Ctor
    Node() : _token()
    {
        _json_id = boost::uuids::random_generator()();
    }

	/// Construct with value and POS
	Node(const std::string & value, const std::string & tag)
    : _token(value,tag)
	{
		_json_id = boost::uuids::random_generator()();
	}

	/// Construct using Token
    Node(Token token): _token(token)
    {
        _json_id = boost::uuids::random_generator()();
    }

	/// Copy constructor
    Node(const Node & rhs) 
	: _token(rhs.as_token())
    {
        this->_json_id = rhs._json_id;
    }

	/// Assignment
    Node & operator=(const Node & rhs) 
    {
        if (this != &rhs){
			this->_token = rhs._token;
            this->_json_id = rhs._json_id;
        }
        return *this;
    }

    virtual ~Node()
	{}

	// Get Node as Token
	Token as_token() const
	{
		return _token;
	}

	/// Get the Token/Node label
	std::string label() const
	{
		return _token.value();
	}

	/// Sort comparison based on Token string
    bool operator<(const Node & rhs) const
    {
        return this->_token < rhs._token;
    }
   
	/// Virtual for Node	
    virtual int token_index() const
    {
        return -1;
    }

    boost::uuids::uuid uuid() const
    {
        return _json_id;
    }

protected:

	friend class boost::serialization::access;
    friend class ConceptualGraph;

	Token _token;
    boost::uuids::uuid _json_id;

    virtual bool is_equal(const Object & rhs) const
    {
        return (this->_token == 
                static_cast<const Node&>(rhs)._token);
    }

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
    {
        ar & _token; 
    }
};
}
///
/// \brief `std::hash` specialization for cgpp::Node
///
/*
namespace std
{
template<> struct hash<cgpp::Node>
{
    inline size_t operator()(const cgpp::Node &arg) const
    {
       std::size_t seed = 0;
       boost::hash_combine(seed, arg.label());
       boost::hash_combine(seed, arg.token_index());
       return seed;
    }
};
}
*/
#endif
