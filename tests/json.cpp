#include <iostream>
#include <memory>
#include "../src/cgpp"
#include "json.hpp"

/// Load Hardcoded JSON strings
/// @see "json.hpp"
int main()
{
    try
    {
        auto jsongraph = std::make_shared<cgpp::ConceptualGraph>(json);
        jsongraph->print();
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
