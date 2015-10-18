// The Art of C++ / Tuple
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tuple.hpp>

#include <type_traits>
#include <cassert>

int main()
{
  using namespace tao;

  auto t = tuple< int, double, int >();
  auto t2 = tuple< int, double, int >( 1, 2, 3 );
  auto t3( t2 );

  auto t4 = tuple< int, double, int >( 1, 2, 2 );
  auto t5 = tuple< int, double, int >( 1, 2, 4 );

  static_assert( tuple_size< decltype( t ) >::value == 3, "oops" );
  static_assert( tuple_size< decltype( t2 ) >::value == 3, "oops" );
  static_assert( tuple_size< decltype( t3 ) >::value == 3, "oops" );

  assert( get< 0 >( t2 ) == 1 );
  assert( get< 1 >( t2 ) == 2 );
  assert( get< 2 >( t2 ) == 3 );

  assert( get< double >( t2 ) == 2 );

  assert( get< 0 >( t3 ) == 1 );
  assert( get< 1 >( t3 ) == 2 );
  assert( get< 2 >( t3 ) == 3 );

  assert( get< double >( t3 ) == 2 );

  assert( t2 == t3 );
  assert( t2 != t4 );
  assert( t2 > t4 );
  assert( t2 < t5 );
  assert( t2 >= t3 );
  assert( t2 <= t3 );
  assert( t2 >= t4 );
  assert( t2 <= t5 );

  assert( tuple<>() == tuple<>() );
  assert( !( tuple<>() < tuple<>() ) );

#if (__cplusplus >= 201402L)

  static_assert( tuple<>() == tuple<>(), "oops" );
  static_assert( make_tuple() == make_tuple(), "oops" );
  static_assert( make_tuple( 0 ) == make_tuple( 0 ), "oops" );

  static_assert( make_tuple( 1, 2, 3 ) > make_tuple( 1, 2, 2 ), "oops" );
  static_assert( make_tuple( 1, 2, 3 ) < make_tuple( 1, 2, 4 ), "oops" );

  // TODO: More constexpr checks

#endif

}
