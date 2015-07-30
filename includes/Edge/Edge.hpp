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
        assert( this->from && this->to && rhs.from && rhs.to );
        return (*this->from == *rhs.from && *this->to == *rhs.to );
    }

    bool operator!= ( const Edge & rhs ) const
    {
        return ( *this == rhs ? false : true );
    }

    bool operator< ( const Edge & rhs )
    {
        assert( this->from && this->to && rhs.from && rhs.to );
        return (*this->from < *rhs.from && *this->to < *rhs.to );
    }

    Edge & operator= ( const Edge & rhs )
    {
        assert( rhs.from && rhs.to );
        if (this != &rhs) // prevent self-assignment
        {
            this->from = std::make_shared<Node>( *rhs.from );
            this->to = std::make_shared<Node>( *rhs.to );
        }
        return *this;
    }

    bool operator< ( const Edge & rhs ) const
    {
        assert( rhs.from && rhs.to );
        return (*this->from) < (*rhs.from) && (*this->to) < (*rhs.to);
    }

    template <class Archive> void serialize ( Archive & archive )
    {
        archive( from, to );
    }

};

}

#endif
