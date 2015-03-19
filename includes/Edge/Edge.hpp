#ifndef _CGPP_Edge_HPP_
#define _CGPP_Edge_HPP_
#pragma once
#include "Includes.hxx"

namespace cgpp {
/**
 * Struct Encapsulating Edges
 *
 * @version 2
 * @date 19-March-2015
 */
struct Edge
{
    std::shared_ptr<Node> from;
    std::shared_ptr<Node> to;

    bool operator== ( const Edge & rhs ) const
    {
        return (*this->from == *rhs.from && *this->to == *rhs.to );
    }

    bool operator!= ( const Edge & rhs ) const
    {
        return ( *this == rhs ? false : true );
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive( from, to );
    }

};

}

#endif
