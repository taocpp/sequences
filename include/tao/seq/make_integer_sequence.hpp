// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_SEQUENCE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_SEQUENCE_HPP

#include <cstddef>
#include <utility>
#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
  namespace seq
  {

#ifdef _LIBCXX_VERSION

    // libc++ already has very efficient versions for make_*

    using std::make_integer_sequence;
    using std::make_index_sequence;
    using std::index_sequence_for;

#else

    // idea from http://stackoverflow.com/a/13073076

    namespace impl
    {
      template< std::size_t, typename, typename >
      struct combine;

      template< std::size_t N, typename T, T... Ns, T... Ms >
      struct combine< N, integer_sequence< T, Ns... >, integer_sequence< T, Ms... > >
      {
        using type = integer_sequence< T, Ns..., ( N + Ms )... >;
      };

      template< typename T, T N, typename = void >
      struct generate;

      template< typename T, T N >
      using generate_t = typename generate< T, N >::type;

      template< typename T, T N >
      struct generate< T, N, typename std::enable_if< ( N > 1 ) >::type >
        : combine< N / 2, generate_t< T, N / 2 >, generate_t< T, N - N / 2 > >
      {};

      template< typename T, T N >
      struct generate< T, N, typename std::enable_if< ( N == 0 ) >::type >
      {
        using type = integer_sequence< T >;
      };

      template< typename T, T N >
      struct generate< T, N, typename std::enable_if< ( N == 1 ) >::type >
      {
        using type = integer_sequence< T, 0 >;
      };
    }

    template< typename T, T N >
    using make_integer_sequence = impl::generate_t< T, N >;

    template< std::size_t N >
    using make_index_sequence = make_integer_sequence< std::size_t, N >;

    template< typename... Ts >
    using index_sequence_for = make_index_sequence< sizeof...( Ts ) >;

#endif

  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_MAKE_INTEGER_SEQUENCE_HPP
