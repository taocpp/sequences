// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/plus.hpp>
#include <tao/seq/minus.hpp>
#include <tao/seq/sum.hpp>
#include <tao/seq/map.hpp>
#include <tao/seq/exclusive_scan.hpp>
#include <tao/seq/inclusive_scan.hpp>

#include <type_traits>

using namespace tao::seq;

template< std::size_t M, typename >
struct count_less_or_equal;

template< std::size_t M, std::size_t... Ns >
struct count_less_or_equal< M, index_sequence< Ns... > >
  : sum< std::size_t, ( ( Ns <= M ) ? 1 : 0 )... >
{};

template< typename, typename >
struct expand;

template< std::size_t... Is, typename S >
struct expand< index_sequence< Is... >, S >
{
  using type = index_sequence< count_less_or_equal< Is, S >::value...  >;
};

template< typename I, typename S >
using expand_t = typename expand< I, S >::type;

int main()
{
  using S = index_sequence< 2, 1, 3, 0, 1, 1, 3 >;
  using I = make_index_sequence< sum< S >::value >;

  static_assert( std::is_same< I, index_sequence< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 > >::value, "oops" );

  using OUTER = expand_t< I, inclusive_scan_t< S > >;
  using INNER = minus_t< I, map_t< OUTER, exclusive_scan_t< S > > >;

  static_assert( std::is_same< OUTER, index_sequence< 0, 0, 1, 2, 2, 2, 4, 5, 6, 6, 6 > >::value, "oops" );
  static_assert( std::is_same< INNER, index_sequence< 0, 1, 0, 0, 1, 2, 0, 0, 0, 1, 2 > >::value, "oops" );
}
