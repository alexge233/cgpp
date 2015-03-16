#include "ConceptualGraph.hpp"

namespace cgpp {

float ConceptualGraph::ratioEdgeVertex ( ) const
{
    return (float)_edges.size() / (float)( _concepts.size() + _relations.size() );
}

float ConceptualGraph::graphSparseness ( ) const
{
    return (float)( _concepts.size() + _relations.size() ) / (float)(_edges.size());
}

float ConceptualGraph::avgPathLength ( ) const
{
    std::vector<unsigned int> lengths;

    // I think I should pass by value, NOT by reference !
    std::function<void ( unsigned int i, unsigned int len )> lambda;
    lambda = [&]( unsigned int i, unsigned int len )
    {
        for ( unsigned int k = i + 1; k < _edges.size(); k++ )
        {
            if ( (*_edges[i].to) == (*_edges[k].from) )
            {
                len++;
                lambda ( k, len );
            }
        }
        // If it reaches this bit here, then: (a) there is no path, or (b) search has been exhausted
        lengths.push_back ( len );
    };

    // Theres already one edge, therefore set to 1
    for ( unsigned int i = 0; i < _edges.size(); i++ )
        lambda ( i, 1 );

    // accumulate lengths
    unsigned int acc = 0;

    if ( lengths.size() > 0 )
    {
        for ( const auto i : lengths ) acc += i;
        return (float)( (float)acc / (float)lengths.size() );
    }
    else
        return 0.f;
}

float ConceptualGraph::treeWidth ( ) const
{
    // http://www.ti.inf.ethz.ch/ew/lehre/GA10/lec-treewidth-new.pdf
    // http://www.cs.ox.ac.uk/people/paul.hunter/papers/GAMES05talk.pdf

    // NOTE: find subgraphs / trees, by finding [Node1] -> [Node2] -> [Node3] or (NodeGroup1) -> (NodeGroup2) -> (NodeGroup3)
    // Count those subgroups, and then divide them by number of total nodes?
    return 0.f;
}

float ConceptualGraph::subgraphRatio ( ) const
{
    // Do the following: 
    //  x = Compute (# of diff edge.from) with (# of diff edge.to)
    //  y = Compute (# of diff edge.from) with (# of same edge.to)
    //  z = (x / y) / # edges ( Branching factor / subgraph ratio )
    return 0.f;
}

float ConceptualGraph::edgePermutations ( ) const
{
    return (float)( _concepts.size() * _relations.size() );
}

}
