// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP
#define TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP

#include <cstddef>

#include "make_integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    // based on http://talesofcpp.fusionfenix.com/post-22/true-story-efficient-packing

    namespace impl
    {
      template< std::size_t, typename T >
      struct indexed
      {
        using type = T;
      };

      template< typename, typename... Ts >
      struct indexer;

      template< std::size_t... Is, typename... Ts >
      struct indexer< index_sequence< Is... >, Ts... >
        : indexed< Is, Ts >...
      {};

      template< std::size_t I, typename T >
      indexed< I, T > select( const indexed< I, T >& );
    }

    template< std::size_t I, typename... Ts >
    using at_index = decltype( impl::select< I >( impl::indexer< index_sequence_for< Ts... >, Ts... >() ) );

    template< std::size_t I, typename... Ts >
    using at_index_t = typename at_index< I, Ts... >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP
