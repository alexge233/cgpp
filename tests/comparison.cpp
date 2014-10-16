#include <iostream>
#include <memory>
#include "../includes/cgpp"
#include "json.hpp"
#include "json2.hpp"

int main ( void )
{
    using namespace cgpp;

    auto graph1 = std::make_shared<cgpp::ConceptualGraph>( json );
    std::cout << "Graph 1" << std::endl;
    graph1->Echo();

    auto graph2 = std::make_shared<cgpp::ConceptualGraph>( json2 );
    std::cout << "Graph 2" << std::endl;
    graph2->Echo();

    bool eq = (*graph1 == *graph2);
    std::cout << "Graphs Equal? " << eq << std::endl;

    return 0;
}