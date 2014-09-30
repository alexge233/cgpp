/**
 * Try All Methods of class ConceptualGraph
 */

#include <memory>
#include "../includes/cgpp"
#include "../includes/Utilities/Utilities.hpp"
#include "json.hpp"

int main ( void )
{
    using namespace cgpp;

    std::cout << "Creating Graph" << std::endl;
    auto graph = std::make_shared<ConceptualGraph>();
<<<<<<< HEAD
    graph->GenerateGUID();
=======
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed

    // Try to manually populate the empty graph
    Token sky = Token( "sky", "NA" );
    Token is = Token( "is", "NA" );
    Token blue = Token( "blue", "NA" );
    
    // 2 Concepts, 1 Relation
    auto sky_node  = std::make_shared<Concept>( sky, 0 );
    auto is_node   = std::make_shared<Relation>( is, 1 );
    auto blue_node = std::make_shared<Concept>( blue, 2 );
    
    // Add them
    graph->AddConcept( sky_node );
    graph->AddConcept( blue_node );
    graph->AddRelation( is_node );
    
    // Connect them
    graph->AddEdge( sky_node, is_node );
    graph->AddEdge( is_node, blue_node );
    
    // Echo
    graph->Echo();
    
    std::cout << "Saving Graph" << std::endl;
    // Save them to file
    graph->Save( "graph_1.bin" );

    std::cout << "Copying Graph" << std::endl;
    // Copy Constructor
    auto copy = std::make_shared<ConceptualGraph>( *graph );
    copy->Echo();
    
    std::cout << "Cmp : Graph == Copy" << std::endl;
    // Test if they are equal - They should be !!
    bool equal = (*graph == *copy);
    std::cout << "Graphs Equal? : " << equal << std::endl;
    
    std::cout << "Cloning Graph" << std::endl;
    auto clone = std::make_shared<ConceptualGraph>( graph->Clone() );
    clone->Echo();
    
    std::cout << "Edges of Relation: " << is_node->asToken()->value() << std::endl;
    
    // Iterate Concepts of relation is
    auto edges1 = graph->Edges( is_node );
    for ( auto concept : edges1 )
    {
        std::cout << "[" << is_node->asToken()->value() << "," << concept->asToken()->value() << "]" << std::endl;
    }
    
    std::cout << "Edges of Concept: " << sky_node->asToken()->value() << std::endl;
    
    // Iterate Relations of Concept sky
    auto edges2 = graph->Edges( sky_node );
    for ( auto relation : edges2 )
    {
        std::cout << "[" << sky_node->asToken()->value() << "," << relation->asToken()->value() << "]" << std::endl;
    }

    std::cout << "Creating Graph2" << std::endl;
    auto graph2 = std::make_shared<ConceptualGraph>();
    
    // manually populate the empty graph
    Token sea = Token( "sea", "NA" );
    auto sea_node = std::make_shared<Concept>( sea, 0 );
    
    // Add them
    graph2->AddConcept( sea_node );
    graph2->AddConcept( blue_node );
    graph2->AddRelation( is_node );
    
    // Connect them
    graph2->AddEdge( sea_node, is_node );
    graph2->AddEdge( is_node, blue_node );
    
    // Echo
    graph2->Echo();
    
    std::cout << "Cmp: Graph == Graph2" << std::endl;
    bool equal2 = (*graph == *graph2);
    std::cout << "Graphs Equal? : " << equal2 << std::endl;
    
    std::cout << "Creating Graph3" << std::endl;
    auto graph3 = std::make_shared<ConceptualGraph>();
<<<<<<< HEAD
    graph3->GenerateGUID();
=======
>>>>>>> f40734ddb950b32196936d5f51c142f056c49fed
    graph3->AddConcept( sea_node );
    graph3->AddConcept( blue_node );
    
    graph3->Echo();
    
    std::cout << "Cmp: Graph3 == Graph2" << std::endl;
    bool equal3 = (*graph3 == *graph2);
    
    std::cout << "Graphs Equal? : " << equal3 << std::endl;
    
    std::cout << "Trying to duplicate Relation,Concepts and Edges in Graph2" << std::endl;
    
    // Try to add existings node and edges and re-test
    graph2->AddConcept( sea_node );
    graph2->AddConcept( blue_node );
    graph2->AddRelation( is_node );
    graph2->AddEdge( sea_node, is_node );
    graph2->AddEdge( is_node, blue_node );
    
    graph2->Echo();
    
    std::cout << "Minimum Edges Connected for Graph: " << util::MinimumEdgesConnected ( graph ) << std::endl;
    std::cout << "Minimum Edges Connected for Graph2: " << util::MinimumEdgesConnected ( graph2 ) << std::endl;
    std::cout << "Minimum Edges Connected for Graph3: " << util::MinimumEdgesConnected ( graph3 ) << std::endl;
    
    std::cout << "JSON for Graph" << std::endl;
    std::cout << graph->JSON() << std::endl;
    
    // Final TEST: try to serialise all graphs
    std::cout << "Adding all graphs into a vector" << std::endl;
    std::vector<std::shared_ptr<ConceptualGraph>> graphs = { graph, copy, clone, graph2, graph3 };
    std::ofstream output ( "graphs.bin" );
    if ( output.is_open() )
    {
        std::cout << "Saving to file: graphs.bin" << std::endl;
        cereal::BinaryOutputArchive archive( output );
        archive ( graphs );
    }
    
    return 0;
}
