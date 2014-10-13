#include "Utilities.hpp"

namespace cgpp
{
namespace util
{

bool MinimumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph )
{
    if ( !graph )
        throw std::runtime_error ( "cgpp::util:: MinimumEdgesConnected: null graph param" );

    const auto concepts = graph->Concepts();
    const auto relations = graph->Relations();
    const auto edges = graph->Edges();

    // Check if there exists at least one Edge from or to that concept - abort if there isn't at least one
    for ( const auto & concept : concepts )
    {
        if ( std::find_if ( edges.begin(), edges.end(),
                            [&]( const Edge & rhs )
                            {
                                if ( rhs.from && rhs.to )
                                        return *rhs.from == *concept || *rhs.to == *concept;

                                else
                                    throw std::runtime_error ( "cgpp::util MinimumEdgesConnected lamda(1): rhs.from or rhs.to is nullptr - Edge problem ?" );
                            }
                            ) == edges.end() )
        {
            return false;
        }
    }
    // Check if there exists at least one Edge from or to that relation - abort if there isn't at least one
    for ( const auto & relation : relations )
    {
        if ( std::find_if ( edges.begin(), edges.end(),
                            [&]( const Edge & rhs )
                            {
                                if ( rhs.from && rhs.to )
                                    return *rhs.from == *relation || *rhs.to == *relation; 

                                else
                                    throw std::runtime_error ( "cgpp::util MinimumEdgesConnected lamda(2): rhs.from or rhs.to is nullptr - Edge problem ?" );
                            }
                            ) == edges.end() )
        {
            return false;
        }
    }
    // If function hasn't returned false so far, we may assume it has the minimum amount of edges
    return true;
}


std::vector<std::shared_ptr<Concept>> Compare_Concepts_Difference (
                                                                    const std::shared_ptr<ConceptualGraph> & lhs,
                                                                    const std::shared_ptr<ConceptualGraph> & rhs
                                                                  )
{
    std::vector<std::shared_ptr<Concept>> diff;

    if ( lhs && rhs )
    {
        const auto mine_concepts = lhs->Concepts();
        const auto other_concepts = rhs->Concepts();

        for ( const auto & concept : mine_concepts )
        {
            // If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
            if ( std::find_if ( other_concepts.begin(), other_concepts.end(),
                                [&]( const std::shared_ptr<Concept> & ptr )
                                {
                                    if ( concept )
                                        return *concept->asToken() == *ptr->asToken();

                                    else
                                        throw std::runtime_error ( "cgpp::util Compare_Concepts_Difference: lamda param concept is null" );
                                }
                              ) == other_concepts.end() )
            {
                diff.push_back ( concept );
            }
        }
    }
    else
        throw std::runtime_error ( "cgpp::util Compare_Concepts_Difference: null graph param" );

    return diff;
}


std::vector<std::shared_ptr<Relation>> Compare_Relations_Difference (
                                                                      const std::shared_ptr<ConceptualGraph> & lhs,
                                                                      const std::shared_ptr<ConceptualGraph> & rhs
                                                                    )

{
    std::vector<std::shared_ptr<Relation>> diff;

    if ( lhs && rhs )
    {
        const auto mine_relations = lhs->Relations();
        const auto other_relations = rhs->Relations();

        for ( const auto & relation : mine_relations )
        {
            // If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
            if ( std::find_if (other_relations.begin(), other_relations.end(),
                                [&]( const std::shared_ptr<Relation> & ptr )
                                {
                                    if ( relation )
                                        return *relation->asToken() == *ptr->asToken();

                                    else
                                        throw std::runtime_error ( "cgpp::util Compare_Relations_Difference: lamda param relation is null" );
                                }
                              ) == other_relations.end() )
            {
                diff.push_back ( relation );
            }
        }
    }
    else
        throw std::runtime_error ( "cgpp::util Compare_Relations_Difference: null graph param" );

    return diff;
}

}

}
