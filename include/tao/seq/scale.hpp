// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP

#include "integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< typename T, T... >
      struct element_type
      {
        using type = T;
      };

      template< typename T, T... Ns >
      struct element_type< integer_sequence< T, Ns... > >
      {
        using type = T;
      };
    }

    template< typename T, typename impl::element_type< T >::type S, T... Ns >
    struct scale
    {
      using type = integer_sequence< T, S * Ns... >;
    };

    template< typename T, T S, T... Ns >
    struct scale< integer_sequence< T, Ns... >, S >
    {
      using type = integer_sequence< T, S * Ns... >;
    };

    template< typename T, typename impl::element_type< T >::type S, T... Ns >
    using scale_t = typename scale< T, S, Ns... >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
