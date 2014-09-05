#include "Utilities.hpp"

namespace cgpp
{
namespace util
{

bool MinimumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph )
{
    if ( graph )
    {
        // Check if there exists at least one Edge from or to that concept - abort if there isn't at least one
        for ( const auto & concept : graph->Concepts() )
        {
            if ( std::find_if ( graph->Edges().begin(), graph->Edges().end(), [&]( const Edge & rhs )
                                                                               { return *rhs.from == *concept || *rhs.to == *concept; } )
                == graph->Edges().end() )
            {
                return false;
            }
        }
        // Check if there exists at least one Edge from or to that relation - abort if there isn't at least one
        for ( const auto & relation : graph->Relations() )
        {
            if ( std::find_if ( graph->Edges().begin(), graph->Edges().end(), [&]( const Edge & rhs )
                                                                               { return *rhs.from == *relation || *rhs.to == *relation; } )
                == graph->Edges().end() )
            {
                return false;
            }
        }
        // If function hasn't returned false so far, we may assume it has the minimum amount of edges
        return true;
    }
    else
        throw std::runtime_error ( "cgpp::util:: MinimumEdgesConnected: null graph param" );
}


bool MaximumEdgesConnected ( const std::shared_ptr<ConceptualGraph> & graph )
{
    // TODO...
    return false;
}


std::vector<std::shared_ptr<Concept>> Compare_Concepts_Difference (
                                                                      const std::shared_ptr<ConceptualGraph> & lhs,
                                                                      const std::shared_ptr<ConceptualGraph> & rhs
                                                                    )
{
    std::vector<std::shared_ptr<Concept>> diff;

    if ( lhs && rhs )
    {
        for ( const auto & concept : lhs->Concepts() )
        {
            // If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
            if ( std::find_if ( rhs->Concepts().begin(), rhs->Concepts().end(), [&]( const std::shared_ptr<Concept> & ptr )
                                                                                  { return *concept->asToken() == *ptr->asToken(); } )
                 == rhs->Concepts().end() )
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
        for ( const auto & relation : lhs->Relations() )
        {
            // If it doesn't exist in rhs->Relations(), add into current diff - comparison takes into account only Token Value
            if ( std::find_if ( rhs->Relations().begin(), rhs->Relations().end(), [&]( const std::shared_ptr<Relation> & ptr )
                                                                                  { return *relation->asToken() == *ptr->asToken(); } )
                 == rhs->Relations().end() )
            {
                diff.push_back ( relation );
            }
        }
    }
    else
        throw std::runtime_error ( "cgpp::util Compare_Relations_Difference: null graph param" );

    return diff;
}


std::vector<std::shared_ptr<Edge>> Compare_Edges_Difference (
                                                                const std::shared_ptr<ConceptualGraph> & lhs,
                                                                const std::shared_ptr<ConceptualGraph> & rhs
                                                              )
{
    // TODO...
}


}
}
