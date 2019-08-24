// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/permutate.hpp>

#include <type_traits>

int main()
{
   using namespace tao::seq;

   using I = index_sequence< 3, 0, 4, 1, 2 >;
   using S = integer_sequence< int, 7, -2, 3, 0, 4 >;
   using R = integer_sequence< int, -2, 0, 4, 7, 3 >;

   static_assert( std::is_same< permutate_t< I, S >, R >::value, "oops" );
}
