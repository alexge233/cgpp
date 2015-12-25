#include <iostream>
#include <memory>
#include "../includes/cgpp"
#include "json.hpp"

int main ( void )
{
    using namespace cgpp;

    Token sky = Token( "sky", "NA" );
    Token is = Token( "is", "NA" );
    Token blue = Token( "blue", "NA" );
    // 2 Concepts, 1 Relation
    auto sky_node  = Concept(sky, 0);
    auto is_node   = Relation(is, 1);
    auto blue_node = Concept(blue, 2);
    auto graph = std::make_shared<ConceptualGraph>();
    // Add them
    graph->add_concept( sky_node );
    graph->add_concept( blue_node );
    graph->add_relation( is_node );
    // Connect them
    graph->add_edge(std::make_shared<Concept>(sky_node), 
					std::make_shared<Relation>(is_node));
    graph->add_edge(std::make_shared<Relation>(is_node),
					std::make_shared<Concept>(blue_node));
    // manually populate the empty graph
    Token sea = Token( "sea", "NA" );
    auto sea_node = Concept(sea, 0);
    auto graph2 = std::make_shared<ConceptualGraph>();
    // Add them
    graph2->add_concept( sea_node );
    graph2->add_concept( blue_node );
    graph2->add_relation( is_node );
    // Connect them
    graph2->add_edge(std::make_shared<Concept>(sea_node), 
					 std::make_shared<Relation>(is_node));
    graph2->add_edge(std::make_shared<Relation>(is_node), 
					 std::make_shared<Concept>(blue_node));
    auto graph3 = std::make_shared<ConceptualGraph>();
    graph3->add_concept( sea_node );
    graph3->add_concept( blue_node );
    graph3->add_relation( is_node );
    // Connect them
    graph3->add_edge(std::make_shared<Concept>(sea_node), 
					 std::make_shared<Relation>(is_node));
    // print
    graph->print();
    graph2->print();
    graph3->print();
    std::cout << std::endl;
 
    std::cout << "Jaccard Coeff(Graph 1, Graph 1) = " 
			  << graph->jaccard_coeff(*graph) << std::endl;
	std::cout << "Sørensen Coeff(Graph 1, Graph 1) = " 
			  << graph->sorensen_coeff(*graph) << std::endl;
	std::cout << "graph1 |= graph1: " << (*graph |= *graph) << std::endl;	
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 1, Graph 2) = " 
			  << graph->jaccard_coeff(*graph2) << std::endl;
    std::cout << "Sørensen Coeff(Graph 1, Graph 2) = " 
			  << graph->sorensen_coeff(*graph2) << std::endl;
	std::cout << "graph1 |= graph2: " << (*graph |= *graph2) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 2, Graph 3) = " 
			  << graph2->jaccard_coeff(*graph3) << std::endl;
    std::cout << "Sørensen Coeff(Graph 2, Graph 3) = " 
			  << graph2->sorensen_coeff(*graph3) << std::endl;
	std::cout << "graph2 |= graph3: " << (*graph2 |= *graph3) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 3, Graph 2) = " 
			  << graph3->jaccard_coeff(*graph2) << std::endl;
    std::cout << "Sørensen Coeff(Graph 3, Graph 2) = " 
			  << graph3->sorensen_coeff(*graph2) << std::endl;
    std::cout << std::endl;

    std::cout << "Jaccard Coeff(Graph 1, Graph 3) = " 
			  << graph->jaccard_coeff(*graph3) << std::endl;
    std::cout << "Sørensen Coeff(Graph 1, Graph 3) = " 
			  << graph->sorensen_coeff(*graph3) << std::endl;
	std::cout << "graph3 |= graph2: " << (*graph3 |= *graph2) << std::endl;
    std::cout << std::endl;

	std::cout << "graph 1 members and their addresses" << std::endl;
	for (const auto & i: graph->concepts())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() << " @ " << &i << std::endl;
	for (const auto & i: graph->relations())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() <<  " @ " << &i << std::endl;
	for (const auto & i: graph->edges())
	{
		std::cout << i.from->label() << " " << i.from->as_token().tag() << " " << i.from->token_index() <<  " @ " << &i.from << std::endl;
		std::cout << i.to->label() << " " << i.to->as_token().tag() << " " << i.to->token_index() << " @ " << &i.to << std::endl;
	}
	std::cout << "graph 2 members and their addresses" << std::endl;
	for (const auto & i: graph2->concepts())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() <<  " @ " << &i << std::endl;
	for (const auto & i: graph2->relations())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() <<  " @ " << &i << std::endl;
	for (const auto & i: graph2->edges())
	{
		std::cout << i.from->label() << " " << i.from->as_token().tag() << " " << i.from->token_index() <<  " @ " << &i.from << std::endl;
		std::cout << i.to->label() << " " << i.to->as_token().tag() << " " << i.to->token_index() <<  " @ " << &i.to << std::endl;
	}
	std::cout << "graph 3 members and their addresses" << std::endl;
	for (const auto & i: graph3->concepts())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() <<  " @ " << &i << std::endl;
	for (const auto & i: graph3->relations())
		std::cout << i.label() << " " << i.as_token().tag() << " " << i.token_index() <<  " @ " << &i << std::endl;
	for (const auto & i: graph3->edges())
	{
		std::cout << i.from->label() << " " << i.from->as_token().tag() << " " << i.from->token_index() <<  " @ " << &i.from << std::endl;
		std::cout << i.to->label() << " " << i.to->as_token().tag() << " " << i.to->token_index() <<  " @ " << &i.to << std::endl;
	}
    return 0;
}
