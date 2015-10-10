// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/map.hpp>
#include <tao/seq/integer_sequence.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  using S = index_sequence< 2, 0, 1, 1, 4, 3, 1, 2, 0 >;
  using M = integer_sequence< int, 11, 88, 42, 0, 99 >;

  static_assert( std::is_same< map_t< index_sequence<>, M >, integer_sequence< int > >::value, "oops" );
  static_assert( std::is_same< map_t< S, M >, integer_sequence< int, 42, 11, 88, 88, 99, 0, 88, 42, 11 > >::value, "oops" );
  static_assert( std::is_same< map_t< S, M >, integer_sequence< int, 42, 11, 88, 88, 99, 0, 88, 42, 11 > >::value, "oops" );
}
