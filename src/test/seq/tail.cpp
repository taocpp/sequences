// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tail.hpp>
#include <tao/seq/integer_sequence.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  static_assert( std::is_same< tail_t< integer_sequence< int, 0 > >, integer_sequence< int > >::value, "oops" );
  static_assert( std::is_same< tail_t< integer_sequence< unsigned, 0 > >, integer_sequence< unsigned > >::value, "oops" );

  static_assert( std::is_same< tail_t< integer_sequence< int, 0, 1 > >, integer_sequence< int, 1 > >::value, "oops" );
  static_assert( std::is_same< tail_t< integer_sequence< unsigned, 0, 1 > >, integer_sequence< unsigned, 1 > >::value, "oops" );

  static_assert( std::is_same< tail_t< integer_sequence< int, 0, 1, 2, 3, 4, 5 > >, integer_sequence< int, 1, 2, 3, 4, 5 > >::value, "oops" );
  static_assert( std::is_same< tail_t< integer_sequence< unsigned, 0, 1, 2, 3, 4, 5 > >, integer_sequence< unsigned, 1, 2, 3, 4, 5 > >::value, "oops" );
}
