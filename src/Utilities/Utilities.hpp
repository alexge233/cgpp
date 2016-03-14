#ifndef _CGPP_Utilities_HPP_
#define _CGPP_Utilities_HPP_
#include "Includes.hxx"
namespace cgpp
{

template <class N>
struct cluster
{
	std::vector<N> nodes;
}

namespace util
{
/**
 * Check if each Node in Graph has at least one Edge
 * @note Each and every Node (Concept/Relation) must have minimum one edge
 * @warning This does NOT check if the graph is fully connected !
 */
bool min_edges_connected(const std::shared_ptr<ConceptualGraph> & graph);

/**
 * Check if all possible Edges exist in @param graph
 * @note Each Node (Concept/Relation) must have an amount of edges equal to the amount of opposite type Nodes
bool MaximumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph );
 */

///
/// @brief Find groups of nodes which have identical edges.
///		   Having indentical edges indicates that a group is a sub-cluster.
///	TODO:  make it a template function
///		   
template <class N>
std::vector<cluster<N>> find_clusters(const std::vector<N> nodes)
{
	// TODO: search and find nodes with identical edges and return them.
}


}
}
#endif
