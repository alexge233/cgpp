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

float ConceptualGraph::sugraphRatio ( ) const
{
    // Do the following: 
    //  x = Compute (# of diff edge.from) with (# of diff edge.to)
    //  y = Compute (# of diff edge.from) with (# of same edge.to)
    //  z = (x / y) / # edges ( Branching factor / subgraph ratio )

    unsigned int same = 0;
    unsigned int diff = 0;
    
    for ( unsigned int i = 0; i < _edges.size(); i++ )
    {
        for ( unsigned int k = i + 1; k < _edges.size(); k++ )
        {
            //std::cout << "[" << _edges[i].from->asToken()->value() << "," << _edges[k].from->asToken()->value() << "] == "
            //          << "[" << _edges[i].to->asToken()->value() << "," << _edges[k].to->asToken()->value() << "]" << std::endl;
                      
            if ( ( (*_edges[i].from) == (*_edges[k].from) ) && ( (*_edges[i].to) == (*_edges[k].to) ) )
                same++;

            else if ( ( (*_edges[i].from) == (*_edges[k].from) ) && ( (*_edges[i].to) != (*_edges[k].to) ) )
                diff++;

            /*
                NOTE: We do not bother with Edges that have a different `From` Node, because they are
                      of no use to calculating branching subgroups.
                      The problem with this, is that we can end up up with NaN's or Inf's.
            */ 
        }
    }

    //std::cout << "same edge.from && edge.to = " << same << std::endl;
    //std::cout << "same edge.from && diff edge.to = " << diff << std::endl;

    float same_norm = (float)same / (float)_edges.size();
    float diff_norm = (float)diff / (float)_edges.size();

    //std::cout << "normalised same = " << same_norm << std::endl;
    //std::cout << "normalised diff = " << diff_norm << std::endl;

    // WARNING - Be prepared to handle NaN and INF !!
    return (float)( same_norm / diff_norm );
}

float ConceptualGraph::edgePermutations ( ) const
{
    return (float)( _concepts.size() * _relations.size() );
}

float ConceptualGraph::nodeSimilarity ( const ConceptualGraph & rhs ) const
{
    //  Count similar and different Nodes (nodes_same, nodes_diff)
    unsigned int same_concepts = 0, same_relations = 0;

    for ( const auto this_concept : this->_concepts )
        for ( const auto other_concept : rhs._concepts )
            if ( *this_concept == *other_concept )
                same_concepts++;

    for ( const auto this_relation : this->_relations )
        for ( const auto other_relation : rhs._relations )
            if ( *this_relation == *other_relation )
                same_relations++;

    // node percentage #(same nodes)  / total ( nodes ) 
    float node_prc = (2.f * (float)(same_concepts + same_relations)) / 
                     (float)( this->_concepts.size() + rhs._concepts.size() + this->_relations.size() + rhs._relations.size() );
                     
    return node_prc;
}

float ConceptualGraph::edgeSimilarity ( const ConceptualGraph & rhs ) const
{
    // Count similar and different Edges (edges_same, edges_diff)
    unsigned int same_edges = 0;

    for ( const auto this_edge : this->_edges )
        for ( const auto other_edge : rhs._edges )
            if ( this_edge == other_edge )
                same_edges++;
            
    // edge percentage #(same edges) / total ( edges )
    float edge_prc = (2.f * (float)same_edges) / 
                     (float)( this->_edges.size() + rhs._edges.size() );
                     
    return edge_prc;
}

}
