// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tuple_cat.hpp>

#include <type_traits>
#include <tuple>

template<std::size_t> void f();

int main()
{
  auto t = tao::seq::tuple_cat( std::make_tuple( 1, true ),
                                std::make_tuple( 1.0 ),
                                std::make_tuple(),
                                std::make_tuple( 1UL, nullptr ) );

  static_assert( std::is_same< decltype( t ), std::tuple< int, bool, double, unsigned long, std::nullptr_t > >::value, "oops" );

  auto t2 = tao::seq::tuple_cat( t, std::make_tuple( 1, true ),
                                 t, std::make_tuple( 1.0 ),
                                 t, std::make_tuple(),
                                 t, std::make_tuple( 1UL, nullptr ) );

  // auto t3 = tao::seq::tuple_cat( t2, std::make_tuple( 1, true ),
  //                                t2, std::make_tuple( 1.0 ),
  //                                t2, std::make_tuple(),
  //                                t2, std::make_tuple( 1UL, nullptr ) );

  // auto t4 = tao::seq::tuple_cat( t3, std::make_tuple( 1, true ),
  //                                t3, std::make_tuple( 1.0 ),
  //                                t3, std::make_tuple(),
  //                                t3, std::make_tuple( 1UL, nullptr ) );

  // auto t5 = tao::seq::tuple_cat( t4, std::make_tuple( 1, true ),
  //                                t4, std::make_tuple( 1.0 ),
  //                                t4, std::make_tuple(),
  //                                t4, std::make_tuple( 1UL, nullptr ) );

  f< std::tuple_size< std::remove_reference< decltype( t2 ) >::type >::value>();

  // static_assert( std::tuple_size< decltype( t5 ) >::value == 0, "oops" );
}
