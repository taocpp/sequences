// Copyright (c) 2019-2020 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/last.hpp>

#include <type_traits>

int main()
{
   using namespace tao::sequence;

   static_assert( last< int, 0 >::value == 0, "oops" );
   static_assert( last< int, 0, 42 >::value == 42, "oops" );
   static_assert( last< int, 0, 1, 2, 3, 4, 5 >::value == 5, "oops" );

   static_assert( last< int, 42 >::value == 42, "oops" );
   static_assert( last< int, 42, 0 >::value == 0, "oops" );
   static_assert( last< int, 42, 1, 2, 3, 4, 5 >::value == 5, "oops" );

   static_assert( last< index_sequence< 0 > >::value == 0, "oops" );
   static_assert( last< index_sequence< 0, 42 > >::value == 42, "oops" );
   static_assert( last< index_sequence< 0, 1, 2, 3, 4, 5 > >::value == 5, "oops" );

   static_assert( std::is_same< last< integer_sequence< int, 0 > >::value_type, int >::value, "oops" );
   static_assert( std::is_same< last< integer_sequence< unsigned, 0 > >::value_type, unsigned >::value, "oops" );
}
