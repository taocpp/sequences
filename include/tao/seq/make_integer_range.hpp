// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP

#include "make_integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< typename T, T Begin, T Steps, T Delta, typename = make_integer_sequence< T, Steps > >
      struct generate_range;

      template< typename T, T B, T S, T D, T... Ns >
      struct generate_range< T, B, S, D, integer_sequence< T, Ns... > >
      {
        using type = integer_sequence< T, B + D * Ns... >;
      };
    }

    template< typename T, T N, T M >
    using make_integer_range = typename impl::generate_range< T, N, ( N <= M ) ? ( M - N ) : ( N - M ), ( N <= M ) ? 1 : -1 >::type;

    template< std::size_t N, std::size_t M >
    using make_index_range = make_integer_range< std::size_t, N, M >;

  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_RANGE_HPP
