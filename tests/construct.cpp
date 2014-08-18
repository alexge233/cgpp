/**
 * TEST conceptual graph manual population & saving
 * TEST Copy Constructor
 * TEST operator==
 */

#include <memory>
#include "../includes/ConceptualGraph/ConceptualGraph.hpp"
#include "json.hpp"

 int main ( void )
 {    
    using namespace cgpp;

    auto graph = std::make_shared<ConceptualGraph>();

    // Try to manually populate the empty graph
    Token sky = Token( "sky", "NA" );
    Token is = Token( "is", "NA" );
    Token blue = Token( "blue", "NA" );
    auto sky_node  = std::make_shared<Concept>( sky, 0 );
    auto is_node   = std::make_shared<Relation>( is, 1 );
    auto blue_node = std::make_shared<Concept>( blue, 2 );
    graph->AddConcept( sky_node );
    graph->AddConcept( blue_node );
    graph->AddRelation( is_node );
    graph->Connect( is_node, sky_node );
    graph->Connect( is_node, blue_node );
    
    graph->Echo();
    graph->Save( "createdgraph_1.bin" );

    // Copy Constructor
    auto copy ( graph );
    copy->Echo();
    copy->Save( "copiedgraph_2.bin" );

    return 0;
 }
