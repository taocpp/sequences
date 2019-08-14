// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/index_of_seq.hpp>
#include <tao/seq/integer_sequence.hpp>

int main()
{
   using namespace tao::seq;

   using S = integer_sequence< int, 7, -2, 3, 0, 4 >;
   using U = integer_sequence< int, 4, 7, -2, 0, 3 >;

   static_assert( std::is_same< index_of_seq_t< S, U >, index_sequence< 4, 0, 1, 3, 2 > >::value, "oops" );
}
