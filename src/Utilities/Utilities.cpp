#include "Utilities.hpp"

namespace cgpp
{
namespace util
{

bool min_edges_set(const ConceptualGraph & graph)
{
    const auto concepts = graph.concepts();
    const auto relations = graph.relations();
    const auto edges = graph.edges();

    // Check if there exists at least one Edge from or to that concept
    for (const auto & concept : concepts)
    {
        if (std::find_if(edges.begin(), edges.end(),
                        [&](const Edge & rhs)
                        {
						    assert(rhs.from && rhs.to);
							return *rhs.from == concept || *rhs.to == concept;
						}) == edges.end() )
        {
            return false;
        }
    }
    // Check if there exists at least one Edge from or to that relation 
    for (const auto & relation : relations)
    {
        if (std::find_if(edges.begin(), edges.end(),
                        [&](const Edge & rhs)
                        {
						    assert(rhs.from && rhs.to);
							return *rhs.from == relation || *rhs.to == relation; 
                        }) == edges.end() )
        {
            return false;
        }
    }
    // If function hasn't returned false so far, 
    // we may assume it has the minimum amount of edges
    return true;
}

std::vector<Concept> concepts_diff(
                                    const ConceptualGraph & lhs,
                                    const ConceptualGraph & rhs
                                  )
{
    std::vector<Concept> diff;
	const auto mine_concepts = lhs.concepts();
	const auto other_concepts = rhs.concepts();

	for (const auto & concept : mine_concepts)
	{
		// If it doesn't exist in rhs->Relations(), add into current diff
        // comparison based only on token ? BUG: use built-in operators!
		if (std::find_if(other_concepts.begin(), other_concepts.end(),
							[&](const Concept & rhs)->bool
							{
								return concept.as_token() == rhs.as_token();
							}) == other_concepts.end())
		{
			diff.push_back(concept);
		}
	}
    return diff;
}

std::vector<Relation> relations_diff(
                                      const ConceptualGraph & lhs,
                                      const ConceptualGraph & rhs
                                    )

{
    std::vector<Relation> diff;
	const auto mine_relations = lhs.relations();
	const auto other_relations = rhs.relations();

	for (const auto & relation : mine_relations)
	{
		// If it doesn't exist in rhs->Relations(), add into current diff - 
        // BUG: comparison takes into account only Token Value
        // TODO: use built-in operators
		if (std::find_if(other_relations.begin(), other_relations.end(),
						[&](const Relation & rhs)->bool
						{
							return relation.as_token() == rhs.as_token();
						}) == other_relations.end())
		{
			diff.push_back(relation);
		}
	}
    return diff;
}

std::vector<cluster<Concept>> concept_clusters(const ConceptualGraph & graph)
{
    auto concepts = graph.concepts();
    std::vector<cgpp::cluster<cgpp::Concept>> clusters;

    std::function<bool(const std::vector<Relation>&, 
                       const std::vector<Relation>&)> lambda =
    [=](const std::vector<Relation> & lhs, const std::vector<Relation> & rhs)
    {
        if (lhs.size() == rhs.size())
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        else
            return false;
    };

    for (unsigned int i = 0; i < concepts.size(); i++)
    {
        cgpp::cluster<cgpp::Concept> group;
        group.nodes.push_back(concepts[i]);
        auto edges_i = graph.has_edges(concepts[i]);
        for (unsigned int k = i + 1; k < concepts.size(); k++)
        {
            if (k < concepts.size())
            {
                auto edges_k = graph.has_edges(concepts[k]);
                if (lambda(edges_i, edges_k))
                    group.nodes.push_back(concepts[k]);
            }
        }
        // more than 1 (no single concepts can form a cluster)
        if (group.nodes.size() > 1)
            clusters.push_back(group);
    }

    // filter: TODO clusters will contain supersets and subsets.
    //              subsets will have identical concepts multiple times.

    return clusters;
}

std::vector<cluster<Relation>> relation_clusters(const ConceptualGraph & graph)
{
    auto relations = graph.relations();
    std::vector<cgpp::cluster<cgpp::Relation>> clusters;

    std::function<bool(const std::vector<Concept>&, 
                       const std::vector<Concept>&)> lambda =
    [=](const std::vector<Concept> & lhs, const std::vector<Concept> & rhs)
    {
        if (lhs.size() == rhs.size())
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        else
            return false;
    };

    for (unsigned int i = 0; i < relations.size(); i++)
    {
        cgpp::cluster<cgpp::Relation> group;
        group.nodes.push_back(relations[i]);
        auto edges_i = graph.has_edges(relations[i]);
        for (unsigned int k = i + 1; k < relations.size(); k++)
        {
            if (k < relations.size())
            {
                auto edges_k = graph.has_edges(relations[k]);
                if (lambda(edges_i, edges_k))
                    group.nodes.push_back(relations[k]);
            }
        }
        // more than 1 (no single relations can form a cluster)
        if (group.nodes.size() > 1)
            clusters.push_back(group);
    }

    // filter: TODO clusters will contain supersets and subsets.
    //              subsets will have identical concepts multiple times.

    return clusters;}
}
}
