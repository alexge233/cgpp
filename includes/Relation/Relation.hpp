#ifndef _CGPP_Relation_HPP_
#define _CGPP_Relation_HPP_
#include "Includes.hxx"
namespace cgpp {
/**
 * @brief Relation as defined by J. Sowa describes relational nodes
 * @author Alex Gkiokas <a.gkiokas@warwick.ac.uk>
 * @date 22-December-2015
 */
class Relation : public Node
{
public:

    Relation() : Node () {}

    /// Construct with Token
    Relation(Token & token) : Node(token) {}

    /// Construct with Token & Token Index
    Relation(
                Token & token,
                int index
            )
    : Node(token),_token_index(index)
    {}

    Relation(const Relation & rhs) : Node(rhs)
    {
        this->_token_index = rhs._token_index;
        this->_json_id = rhs._json_id;
    }
    
    Relation & operator=(const Relation & rhs)
    {
        if (this != &rhs)
        {
            Node::operator=(rhs);
            this->_token_index = rhs._token_index;
        }
        return *this;
    }

	/// Sort comparsion based on Relation's Token Label
    bool operator<(const Relation & rhs) const
    {
        return static_cast<const Node&>(*this) < static_cast<const Node&>(rhs);
    }
    
    ~Relation() = default;

    int token_index() const
    {
        return _token_index;
    }

private:

    friend class ConceptualGraph;
	friend class boost::serialization::access;	

    int _token_index = -1;
        
    bool is_equal(const Object & rhs) const
    {
        return this->_token_index == static_cast<const Relation&>(rhs)._token_index;
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
