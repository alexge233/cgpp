#include <memory>
#include "../src/cgpp"
#include "../src/Utilities/Utilities.hpp"
#include "json.hpp"

#include <boost/serialization/vector.hpp>

int main ( void )
{
    using namespace cgpp;

    auto graph = std::make_shared<ConceptualGraph>();
    std::cout << "Graph 1: " << graph->guid() << std::endl;
    // Try to manually populate the empty graph
    Token sky = Token( "sky", "NA" );
    Token is = Token( "is", "NA" );
    Token blue = Token( "blue", "NA" );
    // 2 Concepts, 1 Relation
    auto sky_node  = Concept( sky, 0 );
    auto is_node   = Relation( is, 1 );
    auto blue_node = Concept( blue, 2 );
    // Add them
    graph->add_concept( sky_node );
    graph->add_concept( blue_node );
    graph->add_relation( is_node );
    // Connect them
    graph->add_edge(std::make_shared<Concept>(sky_node),
					std::make_shared<Relation>(is_node));
    graph->add_edge(std::make_shared<Relation>(is_node),
					std::make_shared<Concept>(blue_node));
    // Echo
    graph->print();
    std::cout << "Saving Graph" << std::endl << std::endl;

    // save them to file
    graph->save("graph_1.bin");
    
	// Copy Constructor
    auto copy = std::make_shared<ConceptualGraph>( *graph );
    std::cout << "Graph Copy: " << copy ->guid() << std::endl;
    copy->print();
	std::cout << std::endl;

    // Test if they are equal - They should be !!
    bool equal = (*graph == *copy);
    std::cout << "original and copy graps equal: " << equal << std::endl << std::endl;

    
    // Iterate Concepts of relation is
    auto edges1 = graph->has_edges(is_node);
	std::cout <<  is_node.label() << " has edges: " << edges1.size() << std::endl;
    for ( auto concept : edges1 )
        std::cout << "[" << is_node.label() << "," << concept.label() << "]" << std::endl;

    // Iterate Relations of Concept sky
    auto edges2 = graph->has_edges( sky_node );
	std::cout  << sky_node.label() << " has edges: " << edges2.size() << std::endl;
    for ( auto relation : edges2 )
        std::cout << "[" << sky_node.label() << "," << relation.label() << "]" << std::endl;
    
	std::cout << std::endl;
	auto graph2 = std::make_shared<ConceptualGraph>();
    std::cout << "Graph2: " <<  graph2->guid() << std::endl;
    Token sea = Token( "sea", "NA" );
    auto sea_node = Concept( sea, 0 );
    // Add them
    graph2->add_concept( sea_node );
    graph2->add_concept( blue_node );
    graph2->add_relation( is_node );
    // Connect them
    graph2->add_edge(std::make_shared<Concept>(sea_node),
					 std::make_shared<Relation>(is_node));
    graph2->add_edge(std::make_shared<Relation>(is_node), 
					 std::make_shared<Concept>(blue_node));
    // Echo
    graph2->print();
	std::cout << std::endl;

    bool equal2 = (*graph == *graph2);
    std::cout << "graph == graph2 equal: " << equal2 << std::endl << std::endl;

    auto graph3 = std::make_shared<ConceptualGraph>();
    std::cout << "graph3: " << graph3->guid() << std::endl;
    graph3->add_concept( sea_node );
    graph3->add_concept( blue_node );
    graph3->print();
	std::cout << std::endl;

    bool equal3 = (*graph3 == *graph2);
    std::cout << "graph3 == graph2 equal: " << equal3 << std::endl << std::endl;

    std::cout << "Duplicating Relation,Concepts and Edges in Graph2" << std::endl;    
    // Try to add existings node and edges and re-test
    graph2->add_concept( sea_node );
    graph2->add_concept( blue_node );
    graph2->add_relation( is_node );
    graph2->add_edge(std::make_shared<Concept>(sea_node),
					 std::make_shared<Relation>(is_node));
    graph2->add_edge(std::make_shared<Relation>(is_node),
					 std::make_shared<Concept>(blue_node));
    graph2->print();

	/*
    std::cout << "Minimum Edges Connected for Graph: " << 
				 util::min_edges_set(graph) << std::endl;
    std::cout << "Minimum Edges Connected for Graph2: " << 
				 util::min_edges_set(graph2) << std::endl;
    std::cout << "Minimum Edges Connected for Graph3: " << 
				 util::min_edges_set(graph3) << std::endl;
	*/

	/*
    std::cout << "JSON for Graph" << std::endl;
    std::cout << graph->json() << std::endl;
    std::cout << "minified JSON for Graph" << std::endl;
    std::cout << graph->minif_json() << std::endl;
    */

    // Final TEST: try to serialise all graphs
	std::vector<ConceptualGraph> graphs = { *graph, *graph2, *graph3 };
    std::ofstream output("graphs.bin");
    if (output.is_open())
    {
		boost::archive::binary_oarchive ar(output);
		ar & graphs;
    }
    return 0;
}
