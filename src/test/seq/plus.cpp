// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/plus.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  using S0 = integer_sequence< int >;
  using LL0 = integer_sequence< long long >;

  static_assert( plus_t< S0, S0 >::size() == 0, "oops" );
  static_assert( plus_t< S0, LL0 >::size() == 0, "oops" );
  static_assert( plus_t< LL0, S0 >::size() == 0, "oops" );
  static_assert( plus_t< LL0, LL0 >::size() == 0, "oops" );

  static_assert( std::is_same< plus_t< S0, S0 >, S0 >::value, "oops" );
  static_assert( std::is_same< plus_t< S0, LL0 >, LL0 >::value, "oops" );
  static_assert( std::is_same< plus_t< LL0, S0 >, LL0 >::value, "oops" );
  static_assert( std::is_same< plus_t< LL0, LL0 >, LL0 >::value, "oops" );

  using S3 = integer_sequence< int, 1, 2, -3 >;
  using LL3 = integer_sequence< long long, 4, 7, 8 >;

  static_assert( std::is_same< plus_t< S3, LL3 >, integer_sequence< long long, 5, 9, 5 > >::value, "oops" );
  static_assert( std::is_same< plus_t< LL3, S3 >, integer_sequence< long long, 5, 9, 5 > >::value, "oops" );
  static_assert( std::is_same< plus_t< LL3, LL3 >, integer_sequence< long long, 8, 14, 16 > >::value, "oops" );
}
