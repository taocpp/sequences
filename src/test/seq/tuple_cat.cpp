// The Art of C++ / Tuple
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tuple.hpp>

#include <type_traits>
#include <cassert>

int main()
{
  using namespace tao;

  auto t = tuple_cat( make_tuple( 1, true ),
                      make_tuple( 2.0 ),
                      make_tuple(),
                      make_tuple( 3UL, nullptr ) );

  static_assert( tuple_size< decltype( t ) >::value == 5, "oops" );
  static_assert( std::is_same< decltype( t ), tuple< int, bool, double, unsigned long, std::nullptr_t > >::value, "oops" );

  assert( get< 0 >( t ) == 1 );
  assert( get< 1 >( t ) == true );
  assert( get< 2 >( t ) == 2.0 );
  assert( get< 3 >( t ) == 3UL );
  assert( get< 4 >( t ) == nullptr );

  assert( get< int >( t ) == 1 );
  assert( get< bool >( t ) == true );
  assert( get< double >( t ) == 2.0 );
  assert( get< unsigned long >( t ) == 3 );
  assert( get< std::nullptr_t >( t ) == nullptr );
}
