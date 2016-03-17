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
    // local copy of concepts
    auto concepts = graph.concepts();

    // edge comparison lambda - use for a node combination
    std::function<bool(const std::vector<Edge>&, 
                       const std::vector<Edge>&)> lambda =
    [=](const std::vector<Edge> & lhs, const std::vector<Edge> & rhs)
    {
        if (lhs.size() == rhs.size())
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        else
            return false;
    };

    // fw iter
    for (unsigned int i = 0; i < concepts.size(); i++)
    {
        auto edges_i = graph.has_edges(concepts[i]);

        for (unsigned int k = i + 1; k < concepts.size(); k++)
        {
            if (k < concepts.size())
            {
                // does nodes[i].edges == nodes[k].edges ?
                // if yes, then we have append to cluste[i]
                // problem is this creates duplicate clusters
                // if not, then move on to next node[k]
                // TODO
            }
        }
    }
}

std::vector<cluster<Relation>> relation_clusters(const ConceptualGraph & graph)
{
    // TODO
}

}
}
