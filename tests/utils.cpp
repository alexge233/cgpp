#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <memory>

#include "../src/cgpp"
#include "json.hpp"

///
/// load complex json graphs, and use utils on them
///
int main()
{
    try
    {
        std::ifstream t("example.json");
        std::stringstream buffer;
        buffer << t.rdbuf();

        auto graph = std::make_shared<cgpp::ConceptualGraph>(buffer.str());
        //graph->print();

        std::cout << "min edges set: " << cgpp::util::min_edges_set(*graph) << std::endl;

		std::cout << std::endl << "Concept clusters: " << std::endl;
        auto cgroup = cgpp::util::concept_clusters(*graph);
        for(const auto & group : cgroup)
        {
			std::cout << "\t";
            for (const auto & node : group.nodes)
                std::cout << node.label() << ", ";
            std::cout << std::endl;
        }
		std::cout << std::endl << "Relation clusters: " << std::endl;
        auto rgroup = cgpp::util::relation_clusters(*graph);
        for(const auto & group : rgroup)
        {
			std::cout << "\t";
            for (const auto & node : group.nodes)
                std::cout << node.label() << ", ";
            std::cout << std::endl;
        }

    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
