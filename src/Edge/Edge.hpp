#ifndef _CGPP_Edge_HPP_
#define _CGPP_Edge_HPP_
#include "Includes.hxx"
namespace cgpp
{
///
/// @brief Edge between Concept and Relation, or Relation and Concept
/// @date 22-December-2015
/// @note the @struct Edge is the owner of shared pointers
///	@warning! Edge can have *same-typed* Nodes, but @class ConceptualGraph won't allow that
///
struct Edge
{
	// from Node and To node, adjacency matrix row
	std::shared_ptr<Node> from;
	std::shared_ptr<Node> to;

	/// Equality: Both Edge nodes must be same
    /// @note comparison based on Node operator (not pointer address)
    bool operator==(const Edge & rhs) const
    {
        assert(this->from && this->to && rhs.from && rhs.to);
        return (*this->from == *rhs.from) && (*this->to == *rhs.to);
    }

	/// inequality
    bool operator!=(const Edge & rhs) const
    {
		assert(this->from && this->to && rhs.from && rhs.to);
        return (*this == rhs ? false : true);
    }

    Edge & operator=(const Edge & rhs)
    {
        assert(rhs.from && rhs.to);
        if (this != &rhs){
            this->from = std::make_shared<Node>(*rhs.from);
            this->to = std::make_shared<Node>(*rhs.to);
        }
        return *this;
    }

	/// Sort comparator based on both Node Token labels
    bool operator<(const Edge & rhs) const
    {
        assert(this->from && this->to && rhs.from && rhs.to);
        return (*this->from) < (*rhs.from) && (*this->to) < (*rhs.to);
    }

	/// Sort comparator (non-const) 
    bool operator<(const Edge & rhs)
    {
        assert(this->from && this->to && rhs.from && rhs.to);
        return (*this->from < *rhs.from && *this->to < *rhs.to);
    }

	friend class boost::serialization::access;

    template <class Archive> 
	void serialize(Archive & ar, const unsigned int)
    {
        ar & from;
		ar & to;
    }

};
}
/*
namespace std
{
template <>
struct hash<cgpp::Edge>
{
    size_t operator()(const cgpp::Edge & rhs) const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, *rhs.from);
        boost::hash_combine(seed, *rhs.to);
        return seed;
    }
};
}
*/
#endif
