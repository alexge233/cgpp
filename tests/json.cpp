/**

    Test JSON deserialisation onto a Conceptual Graph object

 */

#include <iostream>
#include <memory>
#include "../includes/cgpp"
#include "json.hpp"

 int main ( void )
 {
    // TEST: Try to load from this one JSON file - TODO: Try to load from a series of Test JSON files (erroneous and correct ones)
    try
    {
        auto jsongraph = std::make_shared<cgpp::ConceptualGraph>( json );
        jsongraph->Echo();
    }
    catch ( std::exception & e )
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
 }
