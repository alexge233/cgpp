#include <iostream>
#include <memory>
#include "../includes/cgpp"
#include "json.hpp"

int main ( void )
{
    using namespace cgpp;

    std::vector<std::shared_ptr<cgpp::ConceptualGraph>> graphs;

    /**
     * WARNING ATTENTION: This test will fail, because the hardcoded json files in json.hpp have std::size_t murmur hashes.
     * I now use UUID-v4 instead. 
     * Fix the header to be able to use this test!
     */
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json1a ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json1a ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json1b ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json1c ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json2a ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json2b ) );
    graphs.push_back( std::make_shared<cgpp::ConceptualGraph>( json2c ) );

    for ( unsigned int i = 0; i < graphs.size(); i++ )
    {
        if ( i +1 < graphs.size() )
        {
            auto g1 = graphs.at(i);
            auto g2 = graphs.at( i+1 );
            g1->Echo();
            g2->Echo();
            std::cout << "Graphs Equal == " << (*g1 == *g2) << std::endl;
            std::cout << "Graphs Isomorphic |= " << (*g1  |= *g2) << std::endl;
            std::cout << "Graph  Similarity %= " << (*g1 %= *g2) << std::endl;
            std::cout << "Graph  Node Similarity %= " << g1->nodeSimilarity( *g2 ) << std::endl;
            std::cout << "Graph  Edge Similarity %= " << g1->edgeSimilarity( *g2 ) << std::endl;
        }
    }

    return 0;
}