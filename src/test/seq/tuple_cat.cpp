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
#include <tuple>

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

template< typename... Tuples >
struct tuple_helper
{
  using S = index_sequence< std::tuple_size< Tuples >::value... >;
  using I = make_index_sequence< sum< S >::value >;

  using OUTER = expand_t< I, inclusive_scan_t< S > >;
  using INNER = minus_t< I, map_t< OUTER, exclusive_scan_t< S > > >;
};

int main()
{
  using H = tuple_helper< std::tuple< int, long >,
                          std::tuple< unsigned >,
                          std::tuple< short, char, int >,
                          std::tuple<>,
                          std::tuple< long >,
                          std::tuple< unsigned char >,
                          std::tuple< unsigned long, int,int* > >;

  static_assert( std::is_same< H::S, index_sequence< 2, 1, 3, 0, 1, 1, 3 > >::value, "oops" );

  static_assert( std::is_same< H::OUTER, index_sequence< 0, 0, 1, 2, 2, 2, 4, 5, 6, 6, 6 > >::value, "oops" );
  static_assert( std::is_same< H::INNER, index_sequence< 0, 1, 0, 0, 1, 2, 0, 0, 0, 1, 2 > >::value, "oops" );
}
