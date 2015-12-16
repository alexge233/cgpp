#include <iostream>
#include <memory>
#include "../includes/cgpp"

int main ( void )
{
    using namespace cgpp;
    std::cout << "Loading & Deserializing Single File: graph_1.bin" << std::endl;
    auto graph = std::make_shared<ConceptualGraph>();
    graph->load( "graph_1.bin" );
    graph->print();
    std::cout << "Loading & Deserializing all graphs from: graphs.bin" << std::endl;
    std::ifstream input( "graphs.bin" );
    std::vector<std::shared_ptr<ConceptualGraph>> graphs;
    if ( input.is_open() )
    {
        cereal::BinaryInputArchive archive ( input );
        archive( graphs );
    }
    for ( auto g : graphs )
    {
        g->print();
        std::cout << "Graph GUID: " <<  g->guid() << std::endl;
    }
    return 0;
}
