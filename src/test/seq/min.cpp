// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/min.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  static_assert( min< int, 1 >::value == 1, "oops" );
  static_assert( min< int, 1, 0 >::value == 0, "oops" );
  static_assert( min< int, 0, 1 >::value == 0, "oops" );
  static_assert( min< int, 1, -1 >::value == -1, "oops" );
  static_assert( min< int, -1, 1 >::value == -1, "oops" );
  static_assert( min< int, -1, 1, 2 >::value == -1, "oops" );
  static_assert( min< int, -1, 2, 1 >::value == -1, "oops" );
  static_assert( min< int, 2, -1, 1 >::value == -1, "oops" );
  static_assert( min< int, 0, 1, 2, -1, 1, 0, -1, 1 >::value == -1, "oops" );
  static_assert( min< make_index_sequence< 10 > >::value == 0, "oops" );
}
