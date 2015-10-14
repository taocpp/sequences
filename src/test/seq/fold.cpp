// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/fold.hpp>

#include <type_traits>

template< typename T, T A, T B >
using add = std::integral_constant< T, A + B >;

int main()
{
  using namespace tao::seq;

  static_assert( fold< add, int, 1 >::value == 1, "oops" );
  static_assert( fold< add, int, 1, 2 >::value == 3, "oops" );
  static_assert( fold< add, int, 1, 2, 3 >::value == 6, "oops" );

  static_assert( fold< add, int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 >::value == 55, "oops" );
  static_assert( fold< add, int, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 >::value == 66, "oops" );
}
