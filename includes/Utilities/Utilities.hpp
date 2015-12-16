#ifndef _CGPP_Utilities_HPP_
#define _CGPP_Utilities_HPP_
#include "Includes.hxx"
namespace cgpp
{
namespace util
{

/// TODO: RENAME, IMPLEMENT and TEST

/**
 * Check if each Node in Graph has at least one Edge
 * @note Each and every Node (Concept/Relation) must have minimum one edge
 * @warning This does NOT check if the graph is fully connected !
 */
bool MinimumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph );

/**
 * Check if all possible Edges exist in @param graph
 * @note Each Node (Concept/Relation) must have an amount of edges equal to the amount of opposite type Nodes

bool MaximumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph );

 */


/**
 * Find which Concepts don't exist in  both @param lhs and @param rhs Conceptual Graphs
 * @return a vector of different Concepts pointers found in <b 1st parameter rhs>
 */
std::vector<std::shared_ptr<Concept>> Compare_Concepts_Difference (
                                                                    const std::shared_ptr<ConceptualGraph> & lhs,
                                                                    const std::shared_ptr<ConceptualGraph> & rhs
                                                                  );


/**
 * Find which Relations don't exist in  both @param lhs and @param rhs Conceptual Graphs
 * @return a vector of different Relation pointers found in <b 1st parameter rhs>
 */
std::vector<std::shared_ptr<Relation>> Compare_Relations_Difference (
                                                                      const std::shared_ptr<ConceptualGraph> & lhs,
                                                                      const std::shared_ptr<ConceptualGraph> & rhs
                                                                    );


/**
 * Find which Edges don't exist in  both @param lhs and @param rhs Conceptual Graphs
 * @return a vector of different Edge pointers found in <b 1st parameter rhs>

std::vector<std::shared_ptr<Edge>> Compare_Edges_Difference (
                                                              const std::shared_ptr<ConceptualGraph> & lhs,
                                                              const std::shared_ptr<ConceptualGraph> & rhs
                                                            );
 */


/**
 * Find which Concepts are identical in @param lhs and @param rhs Conceptual Graphs
 * @return a vector of pairs of Concept pointers which are identical
 * @note   where: std::pair<0> is the Concept pointer found in lhs, and std::pair<1> is the Concept pointer found in rhs

 std::vector<
             std::pair< std::shared_ptr<Concept>,
                        std::shared_ptr<Concept> >
           > 
           Concepts_Intersection (
                                   const std::shared_ptr<ConceptualGraph> & lhs,
                                   const std::shared_ptr<ConceptualGraph> & rhs
                                 );
 */


/**
 * Find which Relations are identical in @param lhs and @param rhs Conceptual Graphs
 * @return a vector of pairs of Relations pointers which are identical
 * @note   where: std::pair<0> is the Relation pointer found in lhs, and std::pair<1> is the Relation pointer found in rhs

std::vector<
             std::pair< std::shared_ptr<Relation>,
                        std::shared_ptr<Relation> >
           >
           Relations_Intersection (
                                    const std::shared_ptr<ConceptualGraph> & lhs,
                                    const std::shared_ptr<ConceptualGraph> & rhs
                                  );
 */


/**
 * Find which Edges are identical in @param lhs and @param rhs Conceptual Graphs
 * @return a vector of pairs of Edge pointers which are identical
 * @note   where: std::pair<0> is the Edge found in lhs, and std::pair<1> is the Edge found in rhs

std::vector<
             std::pair< std::shared_ptr<Edge>,
                        std::shared_ptr<Edge> >
           >
           Edges_Intersection (
                                const std::shared_ptr<ConceptualGraph> & lhs,
                                const std::shared_ptr<ConceptualGraph> & rhs
                              );

}
 */
}
}
#endif
