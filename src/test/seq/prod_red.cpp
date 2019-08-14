// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <iostream>
#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/prod_red.hpp>

template< typename T, T... Ts >
void print_seq( tao::seq::integer_sequence< T, Ts... > )
{
   (void)std::initializer_list< int >{ ( std::cout << Ts << " ", 0 )... };
   std::cout << std::endl;
}

int main()
{
   using namespace tao::seq;

   static_assert( prod_red_t< integer_sequence< int, -1, 4, 5 > >::value == -20, "ooops" );
}
