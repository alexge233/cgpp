#include <iostream>
#include <memory>
#include "../src/cgpp"
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

int main ( void )
{
    using namespace cgpp;

    std::cout << "Loading & Deserializing Single File: graph_1.bin" << std::endl;

    /// Load directly from a binary file
    auto graph = std::make_shared<ConceptualGraph>();
    graph->load("graph_1.bin");
    graph->print();

	std::cout << std::endl;

    /// Load multiple graphs from a single binary file
    std::cout << "Loading & Deserializing all graphs from: graphs.bin" << std::endl;
    
	std::ifstream input("graphs.bin");
    std::vector<ConceptualGraph> graphs;

    if (input.is_open())
    {
        boost::archive::binary_iarchive ar(input);
        ar & graphs;
    }
    for ( auto g : graphs )
    {
        std::cout << "Graph GUID: " <<  g.guid() << std::endl;
		g.print();
		std::cout << std::endl;
    }
    return 0;
}
