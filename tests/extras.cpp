#include <memory>
#include "../includes/cgpp"

int main ( void )
{
    using namespace cgpp;

    std::cout << "Creating Graph" << std::endl;
    auto graph = std::make_shared<ConceptualGraph>();

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

    // TODO: Try and test: ratioEdgeVertex, graphSparseness, treeWidth, avgPathLength, edgePermutations
    std::cout << "Edge Ratio: " << graph->ratioEdgeVertex() << std::endl;
    std::cout << "Graph Sparseness: " << graph->graphSparseness() << std::endl;
    std::cout << "Edge Permutations: " << graph->edgePermutations() << std::endl;
    std::cout << "Avg Path Length: " << graph->avgPathLength() << std::endl;
}
