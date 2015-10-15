// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP
#define TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP

#include <cstddef>
#include <type_traits>

#include "make_integer_sequence.hpp"

namespace tao
{
  namespace seq
  {
    // based on http://stackoverflow.com/questions/18942322

    namespace impl
    {
      template< std::size_t >
      struct any
      {
        template< typename T > any( T&& ) {}
      };

      template< typename >
      struct wrapper {};

      template< typename >
      struct unwrap;

      template< typename T >
      struct unwrap< wrapper< T > >
      {
        using type = T;
      };

      template< typename >
      struct get_nth_helper;

      template< std::size_t... Is >
      struct get_nth_helper< index_sequence< Is... > >
      {
        template< typename T, typename... Ts >
        static T deduce( any< Is >..., T, Ts&&... );
      };
    }

    template< std::size_t I, typename... Ts >
    struct type_by_index
    {
      using type = typename impl::unwrap< decltype( impl::get_nth_helper< make_index_sequence< I > >::deduce( impl::wrapper< Ts >()... ) ) >::type;
    };

    template< std::size_t I, typename... Ts >
    using type_by_index_t = typename type_by_index< I, Ts... >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP
