// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/exclusive_scan.hpp>
#include <tao/seq/integer_sequence.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  static_assert( std::is_same< exclusive_scan_t< unsigned >, integer_sequence< unsigned > >::value, "oops" );
  static_assert( std::is_same< exclusive_scan_t< int, 2, 3, -1, 0, 4, -1, 1, 1 >, integer_sequence< int, 0, 2, 5, 4, 4, 8, 7, 8 > >::value, "oops" );
}
