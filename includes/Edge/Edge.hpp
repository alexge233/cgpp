#ifndef _CGPP_Edge_HPP_
#define _CGPP_Edge_HPP_ 
#pragma once
#include "Includes.hxx"


namespace cgpp
{

struct Edge
{
  std::shared_ptr<Node> from;
  std::shared_ptr<Node> to;
  
  
  /// TEST
  bool operator== ( const Edge & rhs ) const
  {
      return *this->from == *rhs.from && *this->to == *rhs.to;
  }
  
  
  template <class Archive> void serialize ( Archive & archive )
  {
    archive( from, to );
  }
  
};

}

#endif