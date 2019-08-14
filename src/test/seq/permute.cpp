// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <iostream>
#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/permute.hpp>

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

   static_assert( std::is_same< permute_t< index_sequence< 3, 0, 4, 1, 2 >, S >, integer_sequence< int, -2, 0, 4, 7, 3 > >::value, "oops" );
}
