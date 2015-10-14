// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP

#include <utility>
#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    template< typename, typename >
    struct minus;

    template< typename TA, TA... As, typename TB, TB... Bs >
    struct minus< integer_sequence< TA, As... >, integer_sequence< TB, Bs... > >
    {
      using type = integer_sequence< typename std::common_type< TA, TB >::type, ( As - Bs )... >;
    };

    template< typename A, typename B >
    using minus_t = typename minus< A, B >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_MINUS_HPP
