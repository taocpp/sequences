// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/partial_sum.hpp>
#include <tao/seq/integer_sequence.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  static_assert( partial_sum< 0, int >::value == 0, "empty partial sum failed" );

  static_assert( partial_sum< 0, int, 0 >::value == 0, "0/0 failed" );
  static_assert( partial_sum< 0, int, 1 >::value == 0, "0/1 failed" );
  static_assert( partial_sum< 0, int, 42 >::value == 0, "0/42 failed" );

  static_assert( partial_sum< 1, int, 0 >::value == 0, "1/0 failed" );
  static_assert( partial_sum< 1, int, 1 >::value == 1, "1/1 failed" );
  static_assert( partial_sum< 1, int, 42 >::value == 42, "1/42 failed" );

  static_assert( partial_sum< 1, int, 1, 1 >::value == 1, "1/1+1 failed" );
  static_assert( partial_sum< 2, int, 1, 1 >::value == 2, "2/1+1 failed" );

  static_assert( partial_sum< 0, int, 0, 1, 2, 3 >::value == 0, "0/0+1+2+3 failed" );
  static_assert( partial_sum< 2, int, 0, 1, 2, 3 >::value == 1, "2/0+1+2+3 failed" );
  static_assert( partial_sum< 4, int, 0, 1, 2, 3 >::value == 6, "4/0+1+2+3 failed" );

  using T = integer_sequence< int, 2, 4, 6, 3, 5, 1 >;
  static_assert( partial_sum< 3, T >::value == 12, "3/2+4+6+3+5+1 failed" );
  static_assert( partial_sum< 6, T >::value == 21, "6/2+4+6+3+5+1 failed" );

  static_assert( partial_sum< 0, int, 0, -1, 2, -3 >::value == 0, "0/0+-1+2+-3 failed" );
  static_assert( partial_sum< 1, int, 0, -1, 2, -3 >::value == 0, "1/0+-1+2+-3 failed" );
  static_assert( partial_sum< 2, int, 0, -1, 2, -3 >::value == -1, "2/0+-1+2+-3 failed" );
  static_assert( partial_sum< 3, int, 0, -1, 2, -3 >::value == 1, "3/0+-1+2+-3 failed" );
  static_assert( partial_sum< 4, int, 0, -1, 2, -3 >::value == -2, "4/0+-1+2+-3 failed" );
}
