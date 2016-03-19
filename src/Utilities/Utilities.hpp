#ifndef _CGPP_Utilities_HPP_
#define _CGPP_Utilities_HPP_
#include "Includes.hxx"
namespace cgpp
{

/// cluster struct of N-type Nodes
template <class N> struct cluster
{
	std::vector<N> nodes;

    /// \brief `this` is subset of `arg`
    bool is_subset_of(const cluster &arg) const
    {
        std::vector<N> same;
        std::vector<N> lhs = this->nodes;
        std::vector<N> rhs = arg.nodes;

        std::set_intersection(lhs.begin(),
                              rhs.end(),
                              arg.nodes.begin(),
                              arg.nodes.end(),
                              std::inserter(same, same.begin()));

        // if the intersection is this nodes (identical)
        // then this is a subset of arg
        return (same == lhs ? true : false);
    }
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
std::vector<cluster<Concept>> concept_clusters(const ConceptualGraph & graph);

/// @brief Find clusters of relations which have identical edges.
/// @return a vector of clusters
std::vector<cluster<Relation>> relation_clusters(const ConceptualGraph & graph);

}
}
#endif
