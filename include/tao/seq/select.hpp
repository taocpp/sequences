// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP

#include <cstddef>
#include <utility>

#include "make_integer_sequence.hpp"
#include "sum.hpp"

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< std::size_t, typename S, typename = make_index_sequence< S::size() > >
      struct select;

      template< std::size_t I, typename T, T... Ns, std::size_t... Is >
      struct select< I, integer_sequence< T, Ns... >, index_sequence< Is... > >
        : seq::sum< T, ( ( Is == I ) ? Ns : 0 )... >
      {
        static_assert( I < sizeof...( Is ), "tao::seq::select<I, S>: I is out of range" );
      };
    }

    template< std::size_t I, typename T, T... Ns >
    struct select
      : impl::select< I, integer_sequence< T, Ns... > >
    {};

    template< std::size_t I, typename T, T... Ns >
    struct select< I, integer_sequence< T, Ns... > >
      : impl::select< I, integer_sequence< T, Ns... > >
    {};
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP
