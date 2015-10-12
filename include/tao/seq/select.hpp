// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP

#include <cstddef>
#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< typename T, T... Ns >
      struct values
      {
        static constexpr T data[ sizeof...( Ns ) ] = { Ns... };
      };
    }

    template< std::size_t I, typename T, T... Ns >
    struct select
      : std::integral_constant< T, impl::values< T, Ns... >::data[ I ] >
    {};

    template< std::size_t I, typename T, T... Ns >
    struct select< I, integer_sequence< T, Ns... > >
      : select< I, T, Ns... >
    {};
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_SELECT_HPP
