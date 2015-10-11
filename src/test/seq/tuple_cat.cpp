// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/sum.hpp>
#include <tao/seq/make_integer_sequence.hpp>
#include <tao/seq/inclusive_scan.hpp>
#include <tao/seq/minus.hpp>
#include <tao/seq/map.hpp>
#include <tao/seq/exclusive_scan.hpp>

#include <type_traits>

using namespace tao::seq;

template< std::size_t M, std::size_t... Ns >
struct count_less_or_equal
  : sum< std::size_t, ( ( Ns <= M ) ? 1 : 0 )... >
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

int main()
{
  using S = index_sequence< 2, 1, 3, 0, 1, 1, 3 >;
  using I = make_index_sequence< sum< S >::value >;

  using OUTER = expand_t< I, inclusive_scan_t< S > >;
  using INNER = minus_t< I, map_t< OUTER, exclusive_scan_t< S > > >;

  static_assert( std::is_same< OUTER, index_sequence< 0, 0, 1, 2, 2, 2, 4, 5, 6, 6, 6 > >::value, "oops" );
  static_assert( std::is_same< INNER, index_sequence< 0, 1, 0, 0, 1, 2, 0, 0, 0, 1, 2 > >::value, "oops" );
}
