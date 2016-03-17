#ifndef _CGPP_Edge_HPP_
#define _CGPP_Edge_HPP_
#include "Includes.hxx"
namespace cgpp
{
///
/// @brief Edge between Concept and Relation, or Relation and Concept
/// @date 22-December-2015
///
struct Edge
{
	friend class boost::serialization::access;

	std::shared_ptr<Node> from;
	std::shared_ptr<Node> to;

	/// Equality: Both Edge nodes must be same
    /// @note comparison based on Node operator (not pointer address)
    bool operator==(const Edge & rhs) const
    {
        assert(this->from && this->to && rhs.from && rhs.to);

        // comparison delegated to object::operator==
        return *this->from == *rhs.from && 
			   *this->to == *rhs.to;
    }

	/// inequality
    bool operator!=(const Edge & rhs) const
    {
        return *this == rhs;
    }

    Edge & operator=(const Edge & rhs)
    {
        assert(rhs.from && rhs.to);
        if (this != &rhs)
        {
            this->from = std::make_shared<Node>(*rhs.from);
            this->to = std::make_shared<Node>(*rhs.to);
        }
        return *this;
    }

	/// Sort comparator based on both Node Token labels
    bool operator<(const Edge & rhs) const
    {
        assert(rhs.from && rhs.to);
        return (*this->from) < (*rhs.from) 
               && (*this->to) < (*rhs.to);
    }

	/// Sort comparator (non-const) 
    bool operator<(const Edge & rhs)
    {
        assert(this->from && this->to && rhs.from && rhs.to);
        return (*this->from < *rhs.from 
               && *this->to < *rhs.to);
    }

    template <class Archive> 
	void serialize(Archive & ar, const unsigned int)
    {
        ar & from;
		ar & to;
    }

};
}
#endif
