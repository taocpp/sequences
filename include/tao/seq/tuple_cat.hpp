// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_TUPLE_CAT_HPP
#define TAOCPP_SEQUENCES_INCLUDE_TUPLE_CAT_HPP

#include "integer_sequence.hpp"
#include "make_integer_sequence.hpp"
#include "sum.hpp"
#include "type_by_index.hpp"
#include "inclusive_scan.hpp"
#include "minus.hpp"
#include "map.hpp"
#include "exclusive_scan.hpp"

#include <cstddef>
#include <tuple>

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      template< std::size_t M, std::size_t... Ns >
      struct count_less_or_equal
        : seq::sum< std::size_t, ( ( Ns <= M ) ? 1 : 0 )... >
      {};

      template< typename, typename >
      struct expand;

      template< std::size_t... Is, std::size_t... Ns >
      struct expand< index_sequence< Is... >, index_sequence< Ns... > >
      {
        using type = index_sequence< count_less_or_equal< Is, Ns... >::value...  >;
      };

      template< typename I, typename S >
      using expand_t = typename expand< I, S >::type;

      template< std::size_t, typename >
      struct tuple_type_by_index;

      template< std::size_t I, typename... Ts >
      struct tuple_type_by_index< I, std::tuple< Ts... > >
        : type_by_index< I, Ts... >
      {};

      template< std::size_t I, typename T >
      using tuple_type_by_index_t = typename tuple_type_by_index< I, T >::type;

      template< typename... >
      struct tuple_cat_result;

      template< std::size_t... Os, std::size_t... Is, typename... Ts >
      struct tuple_cat_result< index_sequence< Os... >, index_sequence< Is... >, Ts... >
      {
        using type = std::tuple< tuple_type_by_index_t< Is, type_by_index_t< Os, Ts... > >... >;
      };

      template< typename... Ts >
      using tuple_cat_result_t = typename tuple_cat_result< Ts... >::type;

      template< typename... Tuples >
      struct tuple_helper
      {
        using S = index_sequence< std::tuple_size< Tuples >::value... >;
        using I = make_index_sequence< seq::sum< S >::value >;

        using outer_index_sequence = expand_t< I, inclusive_scan_t< S > >;
        using inner_index_sequence = minus_t< I, map_t< outer_index_sequence, exclusive_scan_t< S > > >;

        using result_type = tuple_cat_result_t< outer_index_sequence, inner_index_sequence, Tuples... >;
      };

      template< typename R, std::size_t... Os, std::size_t... Is, typename Tuples >
      R tuple_cat( index_sequence< Os... >, index_sequence< Is... >, Tuples tuples )
      {
        return R( std::get< Is >( std::get< Os >( tuples ) )... );
      }
    }

    template< typename... Ts, typename H = impl::tuple_helper< Ts... >, typename R = typename H::result_type >
    R tuple_cat( Ts&&... ts )
    {
      return impl::tuple_cat< R >( typename H::outer_index_sequence(), typename H::inner_index_sequence(), std::forward_as_tuple( std::forward< Ts >( ts )... ) );
    }
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_TUPLE_CAT_HPP
