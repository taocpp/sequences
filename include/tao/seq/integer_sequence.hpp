// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_INTEGER_SEQUENCE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_INTEGER_SEQUENCE_HPP

#if __cplusplus >= 201402L
#include <utility>
#else
#include <cstddef>
#endif

namespace tao
{
  namespace seq
  {

#if __cplusplus >= 201402L

    using std::integer_sequence;
    using std::index_sequence;

#else

    template< typename T, T... Ns >
    struct integer_sequence
    {
      using value_type = T;

      static constexpr std::size_t size() noexcept
      {
        return sizeof...( Ns );
      }
    };

    template< std::size_t... Ns >
    using index_sequence = integer_sequence< std::size_t, Ns... >;

#endif

  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_INTEGER_SEQUENCE_HPP
