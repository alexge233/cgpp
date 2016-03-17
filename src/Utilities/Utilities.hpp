#ifndef _CGPP_Utilities_HPP_
#define _CGPP_Utilities_HPP_
#include "Includes.hxx"
namespace cgpp
{

/// cluster struct of N-type Nodes
template <class N> struct cluster
{
	std::vector<N> nodes;
};

namespace util
{
/**
 * Check if each Node in Graph has at least one Edge
 * @note Each and every Node (Concept/Relation) must have minimum one edge
 * @warning This does NOT check if the graph is fully connected !
 */
bool min_edges_set(const ConceptualGraph & graph);

/// @brief find different concepts
/// @return a list of the different concepts
std::vector<Concept> concepts_diff(
                                    const ConceptualGraph & lhs,
                                    const ConceptualGraph & rhs
                                  );

/// @brief find different concepts
/// @return a list of the different concepts
std::vector<Relation> relation_diff(
                                    const ConceptualGraph & lhs,
                                    const ConceptualGraph & rhs
                                   );

/// @brief Find clusters of concepts which have identical edges.
/// @return a vector of clusters
std::vector<cluster<Concept>> concept_clusters(const std::vector<Concept> nodes);

/// @brief Find clusters of relations which have identical edges.
/// @return a vector of clusters
std::vector<cluster<Relation>> relation_clusters(const std::vector<Relation> nodes);

}
}
#endif
