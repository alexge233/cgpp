#ifndef _CGPP_Relation_HPP_
#define _CGPP_Relation_HPP_
#pragma once
#include "Includes.hxx"

namespace cgpp
{

/**
 * Relation as defined by J. Sowa describes relational nodes
 * Only relations may have edges to Concepts
 *
 * @version 6
 * @date 8-August-2014
 */

class Relation : public Node
{
  public:
    
    
    /// Empty Constructor - Avoid using
    Relation ( ) = default;

    /// Construct with Token
    Relation ( Token & token ) : Node( token )
    { }

    /// Construct with Token & Token Index
    Relation (
    		   Token & token,
	    	   int index
		     )
    : Node ( token ), _token_index ( index )
    { }

    /// Construct using another relation
    Relation ( const Relation & rhs ) 
    : Node( rhs )
    {
        /// WARNING: Shallow copy of the pointers
        this->_edges = rhs._edges;
        this->_token_index = rhs._token_index;
    }
    
    /// Poly Destructor
    ~Relation ( ) = default;


    /// Clone: Deep copy - TEST that its fullproof
    std::shared_ptr<Relation> Clone ( ) const
    {
        return std::make_shared<Relation>( * this );
    }


    /// Equality Operator - NOTE: matches Edges (order)
    bool operator== ( const Relation & rhs ) const
    {
        bool tokenTest = (*this->_token) ==  (*rhs._token);
        bool edgesTest = false;
      
        if ( this->_edges.size() == rhs._edges.size() )
        {
            // std::equal checks that edges match both items (concepts) and order (concept sequence)
            edgesTest = std::equal( this->_edges.begin(), this->_edges.end(), rhs._edges.begin(),
                                    [&]( const std::shared_ptr<Concept> & lhs, const std::shared_ptr<Concept> & rhs) -> bool
                                    {
                                        // TODO: Fix = Compare value & node position (the operator==) so maybe use a different version of std::equal without a lambda?
                                        return (*lhs == *rhs);
                                    });
        }
      
        return tokenTest && edgesTest;
    }


    /// Get Token Index
    int TokenIndex ( ) const
    {
        return _token_index;
    }

    /// Get Current Edges
    std::vector<std::shared_ptr<Concept>> Edges ( ) const
    {
        return _edges;
    }

    /// Create an Edge to @param node
    bool Edge ( const std::shared_ptr<Concept> node )
    {
       if ( node )
       {
            /// Find by pointer address (NOTE: why ??? I dont care about memory mgmt, so why not just compare Concepts ??? ) BUG: identical Concept may exist twice as a diff pointer !
            auto it = std::find_if ( _edges.begin(), _edges.end(), [&]( const std::shared_ptr<Concept> & ptr ){ return ptr == node; });

            /// Doesn't exist - Add Edge
            if ( it == _edges.end() )
            {
              _edges.push_back( node );
              return true;
            }
            else
              return false;
      }
      else
        throw std::runtime_error ( "Relation Edge param null node" );
    }

    
    
  private:
    
    friend class ConceptualGraph;
    friend class cereal::access;
    
    int _token_index = -1;

    std::vector<std::shared_ptr<Concept>> _edges;


    template <class Archive> 
    void serialize ( Archive & archive )
    {
        archive ( cereal::base_class<Node>( this ) );
        archive ( _token_index );
        archive ( _edges );
    }

    
};

}
#endif

