#include <memory>
#include "../includes/ConceptualGraph/ConceptualGraph.hpp"
#include "json.hpp"

int main ( void )
{    
  using namespace cgpp;

  auto graph = std::make_shared<ConceptualGraph>();
  graph->Load( "createdgraph_1.bin" );
  graph->Echo();
  
  return 0;
}