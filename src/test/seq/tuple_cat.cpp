// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tuple_cat.hpp>

#include <type_traits>
#include <tuple>

int main()
{
  auto t = tao::seq::tuple_cat( std::make_tuple( 1, true ),
                                std::make_tuple( 1.0 ),
                                std::make_tuple( 1UL, nullptr ) );

  static_assert( std::is_same< decltype( t ), std::tuple< int, bool, double, unsigned long, std::nullptr_t > >::value, "oops" );
}
