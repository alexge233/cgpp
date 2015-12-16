#include <iostream>
#include <memory>
#include "../includes/cgpp"
#include "json.hpp"

int main ( void )
{
    using namespace cgpp;

    /* 
    std::vector<std::shared_ptr<cgpp::ConceptualGraph>> graphs;
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
            g1->print();
            g2->print();
            //std::cout << "Graphs Equal == " << (*g1 == *g2) << std::endl;
            //std::cout << "Graphs Isomorphic |= " << (*g1  |= *g2) << std::endl;
            std::cout << "Graph  Similarity %= " << (*g1 %= *g2) << std::endl;
            //std::cout << "Graph  Node Similarity %= " << g1->nodeSimilarity( *g2 ) << std::endl;
            //std::cout << "Graph  Edge Similarity %= " << g1->edgeSimilarity( *g2 ) << std::endl;
        }
    }
    */

    Token sky = Token( "sky", "NA" );
    Token is = Token( "is", "NA" );
    Token blue = Token( "blue", "NA" );
    // 2 Concepts, 1 Relation
    auto sky_node  = std::make_shared<Concept>( sky, 0 );
    auto is_node   = std::make_shared<Relation>( is, 1 );
    auto blue_node = std::make_shared<Concept>( blue, 2 );
    auto graph = std::make_shared<ConceptualGraph>();
    // Add them
    graph->AddConcept( sky_node );
    graph->AddConcept( blue_node );
    graph->AddRelation( is_node );
    // Connect them
    graph->AddEdge( sky_node, is_node );
    graph->AddEdge( is_node, blue_node );
    // manually populate the empty graph
    Token sea = Token( "sea", "NA" );
    auto sea_node = std::make_shared<Concept>( sea, 0 );
    auto graph2 = std::make_shared<ConceptualGraph>();
    // Add them
    graph2->AddConcept( sea_node );
    graph2->AddConcept( blue_node );
    graph2->AddRelation( is_node );
    // Connect them
    graph2->AddEdge( sea_node, is_node );
    graph2->AddEdge( is_node, blue_node );
    auto graph3 = std::make_shared<ConceptualGraph>();
    graph3->AddConcept( sea_node );
    graph3->AddConcept( blue_node );
    graph3->AddRelation( is_node );
    // Connect them
    graph3->AddEdge( sea_node, is_node );
    
    // print
    std::cout << "Graph 1" << std::endl;
    graph->print();
    std::cout << "Graph 2" << std::endl;
    graph2->print();
    std::cout << "Graph 3" << std::endl;
    graph3->print();
    std::cout << std::endl;
 
    std::cout << "Jaccard Coeff(Graph 1, Graph 1) = " << graph->jaccard_coeff(*graph) << std::endl;
    std::cout << "Sørensen Coeff(Graph 1, Graph 1) = " << graph->sorensen_coeff(*graph) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 1, Graph 2) = " << graph->jaccard_coeff(*graph2) << std::endl;
    std::cout << "Sørensen Coeff(Graph 1, Graph 2) = " << graph->sorensen_coeff(*graph2) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 2, Graph 3) = " << graph2->jaccard_coeff(*graph3) << std::endl;
    std::cout << "Sørensen Coeff(Graph 2, Graph 3) = " << graph2->sorensen_coeff(*graph3) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 3, Graph 2) = " << graph3->jaccard_coeff(*graph2) << std::endl;
    std::cout << "Sørensen Coeff(Graph 3, Graph 2) = " << graph3->sorensen_coeff(*graph2) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 1, Graph 3) = " << graph->jaccard_coeff(*graph3) << std::endl;
    std::cout << "Sørensen Coeff(Graph 1, Graph 3) = " << graph->sorensen_coeff(*graph3) << std::endl;
    std::cout << std::endl;

    return 0;
}
