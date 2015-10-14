// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_PLUS_HPP
#define TAOCPP_SEQUENCES_INCLUDE_PLUS_HPP

#include <utility>
#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    template< typename, typename >
    struct plus;

    template< typename TA, A... As, typename TB, B... Bs >
    struct plus< integer_sequence< TA, As... >, integer_sequence< TB, Bs... > >
    {
      using type = integer_sequence< typename std::common_type< TA, TB >::type, ( As + Bs )... >;
    };

    template< typename A, typename B >
    using plus_t = typename plus< A, B >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_PLUS_HPP
