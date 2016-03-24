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
    return true;
}

std::vector<Concept> concepts_diff(
                                    const ConceptualGraph & lhs,
                                    const ConceptualGraph & rhs
                                  )
{
	const auto lhs_c = lhs.concepts();
	const auto rhs_c = rhs.concepts();
	std::vector<Concept> diff;
	std::set_difference(lhs_c.begin(), lhs_c.end(),
						rhs_c.begin(), rhs_c.end(),
						std::inserter(diff, diff.end()));
	return diff;
}

std::vector<Relation> relations_diff(
                                      const ConceptualGraph & lhs,
                                      const ConceptualGraph & rhs
                                    )

{
	const auto lhs_r = lhs.relations();
	const auto rhs_r = rhs.relations();
    std::vector<Relation> diff;
	std::set_difference(lhs_r.begin(), lhs_r.end(),
						rhs_r.begin(), rhs_r.end(),
						std::inserter(diff, diff.begin()));
	return diff;
}

std::vector<cluster<Concept>> concept_clusters(const ConceptualGraph & graph)
{
    auto concepts = graph.concepts();
    std::vector<cluster<Concept>> clusters;
    std::function<bool(const std::vector<Relation>&, const std::vector<Relation>&)> lambda =
    [=](const std::vector<Relation> & lhs, const std::vector<Relation> & rhs)
    {
        if (lhs.size() == rhs.size())
            return std::equal(lhs.begin(), lhs.end(), rhs.begin());
        else
            return false;
    };
    for (unsigned int i = 0; i < concepts.size(); i++)
    {
        cluster<Concept> group;
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
        if (group.nodes.size() > 1)
		{
			bool add = true;
			for (auto & lhs : clusters)
			{
				if (lhs.is_superset_of(group)){
					add = false;
					break;
				}
				if (group.is_superset_of(lhs)){
					add = false;
					std::swap(lhs, group);
				}
			}
			if (add) 
				clusters.push_back(group);
		}
    }
    return clusters;
}

std::vector<cluster<Relation>> relation_clusters(const ConceptualGraph & graph)
{
    auto relations = graph.relations();
    std::vector<cgpp::cluster<cgpp::Relation>> clusters;
    std::function<bool(const std::vector<Concept>&, const std::vector<Concept>&)> lambda =
    [=](const std::vector<Concept>& lhs, const std::vector<Concept>& rhs)
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
		if (group.nodes.size() > 1)
		{
			bool add = true;
			for (auto & lhs : clusters)
			{
				if (lhs.is_superset_of(group)){
					add = false;
					break;
				}
				if (group.is_superset_of(lhs)){
					add = false;
					std::swap(lhs, group);
				}
			}
			if (add) 
				clusters.push_back(group);
		}
    }
    return clusters;
}

}
}
