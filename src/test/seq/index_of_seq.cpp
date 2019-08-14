// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <iostream>
#include <tao/seq/index_of_seq.hpp>
#include <tao/seq/integer_sequence.hpp>

template< typename T, T... Ts >
void print_seq( tao::seq::index_sequence< Ts... > )
{
   (void)std::initializer_list< int >{ ( std::cout << Ts << " ", 0 )... };
   std::cout << std::endl;
}

int main()
{
   using namespace tao::seq;

   using S = integer_sequence< int, 7, -2, 3, 0, 4 >;
   using U = integer_sequence< int, 4, 7, -2, 0, 3 >;

   static_assert( std::is_same< index_of_seq_t< S, U >, index_sequence< 4, 0, 1, 3, 2 > >::value, "oops" );
}
