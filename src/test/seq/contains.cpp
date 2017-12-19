// Copyright (c) 2017 Michiel van Slobbe <mvslobbe@athenacr.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/contains.hpp>

#include <type_traits>

int main()
{
   using namespace tao::seq;

   using S = integer_sequence< int, 4, 7, -2, 0, 3 >;
   using U = integer_sequence< unsigned, 42 >;

   static_assert( contains< S, 4 >::value, "oops" );
   static_assert( contains< S, 7 >::value, "oops" );
   static_assert( contains< S, -2 >::value, "oops" );
   static_assert( ! contains< S, 1 >::value, "oops" );

   static_assert( contains< U, 42 >::value, "oops" );
   static_assert( ! contains< U, 388075 >::value, "oops" );
}
