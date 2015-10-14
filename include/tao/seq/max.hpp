// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_MAX_HPP
#define TAOCPP_SEQUENCES_INCLUDE_MAX_HPP

#include "fold.hpp"

#include <type_traits>

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< typename T, T A, T B >
      using max = std::integral_constant< T, ( ( A > B ) ? A : B ) >;
    }

    template< typename T, T... Ns >
    using max = fold< impl::max, T, Ns... >;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_MAX_HPP
