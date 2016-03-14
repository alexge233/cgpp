#include "Utilities.hpp"

namespace cgpp
{
namespace util
{

bool MinimumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph )
{
    if ( !graph )
        throw std::runtime_error ( "cgpp::util:: MinimumEdgesConnected: null graph param" );

    const auto concepts = graph->concepts();
    const auto relations = graph->relations();
    const auto edges = graph->edges();

    // Check if there exists at least one Edge from or to that concept - abort if there isn't at least one
    for ( const auto & concept : concepts )
    {
        if ( std::find_if(edges.begin(), edges.end(),
                          [&]( const Edge & rhs )
                          {
							assert(rhs.from && rhs.to);
							return *rhs.from == concept || *rhs.to == concept;
						  }) == edges.end() )
        {
            return false;
        }
    }
    // Check if there exists at least one Edge from or to that relation - abort if there isn't at least one
    for ( const auto & relation : relations )
    {
        if ( std::find_if(edges.begin(), edges.end(),
                          [&]( const Edge & rhs )
                          {
							  assert(rhs.from && rhs.to);
							  return *rhs.from == relation || *rhs.to == relation; 
                          }) == edges.end() )
        {
            return false;
        }
    }
    // If function hasn't returned false so far, we may assume it has the minimum amount of edges
    return true;
}

std::vector<Concept> Compare_Concepts_Difference (
													const std::shared_ptr<ConceptualGraph> & lhs,
													const std::shared_ptr<ConceptualGraph> & rhs
												  )
{
    std::vector<Concept> diff;
    assert(lhs && rhs);
	const auto mine_concepts = lhs->concepts();
	const auto other_concepts = rhs->concepts();

	for ( const auto & concept : mine_concepts )
	{
		// If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
		if ( std::find_if ( other_concepts.begin(), other_concepts.end(),
							[&](const Concept & rhs)->bool
							{
								return concept.as_token() == rhs.as_token();
							}) == other_concepts.end() )
		{
			diff.push_back(concept);
		}
	}
    return diff;
}

std::vector<Relation> Compare_Relations_Difference (
													  const std::shared_ptr<ConceptualGraph> & lhs,
													  const std::shared_ptr<ConceptualGraph> & rhs
													)

{
    std::vector<Relation> diff;
    assert(lhs && rhs);
	const auto mine_relations = lhs->relations();
	const auto other_relations = rhs->relations();

	for ( const auto & relation : mine_relations )
	{
		// If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
		if ( std::find_if (other_relations.begin(), other_relations.end(),
						   [&](const Relation & rhs)->bool
							{
								return relation.as_token() == rhs.as_token();
							}) == other_relations.end() )
		{
			diff.push_back(relation);
		}
	}
    return diff;
}

}

}
