#ifndef _CGPP_Concept_HPP_
#define _CGPP_Concept_HPP_
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Concept node as described by J. Sowa
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @date 22-December-2015
 */
class Concept : public Node
{
public:

    Concept() : Node() 
	{}

    /// Construct with Token
    Concept(Token & token) : Node(token)
	{}

    /// Construct using Token and Token Index
    Concept(
              Token & token,
              int index
           )
    : Node(token),_token_index(index)
    {}

	/// Copy Constructor
    Concept(const Concept & rhs) : Node(rhs)
    {
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }

	/// Assignment
    Concept & operator=(const Concept & rhs)
    {
        if (this != &rhs){
            Node::operator=(rhs);
            this->_token_index = rhs._token_index;
        }
        return *this;
    }

	/// Sort comparator based on Token (label & POS tag)
    bool operator<(const Concept & rhs)
    {
        return static_cast<const Node&>(*this) < static_cast<const Node&>(rhs);
    }

	/// Addition (concatenation) of two Concepts creates a new one
	Concept operator+(const Concept &rhs)
	{
		/// TODO: allocate and assign values, token index and json id (if applicable)
		/// WARNING: what happens to edges? Do we invalidate them?
		/// This is complex and tricky
	}

	/// Addition (concatenation) of multiple Concepts into a new one
	Concept operator+(std::vector<Concept> & nodes)
	{
		/// TODO: allocate and assign values, token index and json id (if applicable)
		/// TODO: should I use a vector param, deque or maybe a map/set ?
		/// WARNING: what happens to edges? Do we invalidate them?
	}

    ~Concept() = default;

	/// token index
    int token_index() const
    {
        return _token_index;
    }

private:

    friend class ConceptualGraph;
	friend class boost::serialization::access;

    int _token_index = -1;
    
    bool is_equal(const Object &rhs) const
    {
        return this->_token_index == static_cast<const Concept&>(rhs)._token_index;
    }

	template<class Archive>
	void serialize(Archive & ar, const unsigned int)
	{
		ar & boost::serialization::base_object<Node>(*this);
		ar & _token_index;
	}
};
}
#endif
