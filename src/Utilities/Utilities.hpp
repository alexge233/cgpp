#ifndef _CGPP_Utilities_HPP_
#define _CGPP_Utilities_HPP_
#include "Includes.hxx"
namespace cgpp
{

/// cluster struct of N-type Nodes
template <class N> struct cluster
{
	std::vector<N> nodes;

	std::vector<N> set_intersection(const cluster<N> rhs) const
	{
		std::vector<N> common;
		std::vector<N> A = this->nodes;
		std::vector<N> B = rhs.nodes;
		std::sort(A.begin(), A.end());
		std::sort(B.begin(), B.end());
		std::set_intersection(A.begin(), A.end(),
							  B.begin(), B.end(),
							  std::inserter(common, common.begin()));
		return common;
	}

	std::vector<N> set_difference(const cluster<N> rhs) const
	{
		std::vector<N> diff;
		std::vector<N> A = this->nodes;
		std::vector<N> B = rhs.nodes;
		std::sort(A.begin(), A.end());
		std::sort(B.begin(), B.end());
		std::set_difference(A.begin(), A.end(),
							B.begin(), B.end(),
							std::inserter(diff, diff.begin()));
		return diff;
	}

	bool is_superset_of(const cluster<N> rhs) const
	{
		std::vector<N> A = this->nodes;
		std::vector<N> B = rhs.nodes;
		return std::includes(A.begin(), A.end(),
							 B.begin(), B.end());
	}

	bool is_subset_of(const cluster<N> rhs) const
	{
		std::vector<N> A = this->nodes;
		std::vector<N> B = rhs.nodes;
		return std::includes(B.begin(), B.end(),
							 A.begin(), A.end());
	}	
};

namespace util
{

/// Check if each Node in Graph has at least one Edge
/// @note Each and every Node (Concept/Relation) must have minimum one edge
/// @warning This does NOT check if the graph is fully connected !
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
/// @note returns sub-sets of super-cluster in order to provide variations
std::vector<cluster<Concept>> concept_clusters(const ConceptualGraph & graph);

/// @brief Find clusters of relations which have identical edges.
/// @return a vector of clusters
/// @note returns sub-sets of same super-cluster in order to provide variations
std::vector<cluster<Relation>> relation_clusters(const ConceptualGraph & graph);

}
}
#endif
