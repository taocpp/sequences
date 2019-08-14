// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <iostream>
#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/prod.hpp>

template< typename T, T... Ts >
void print_seq( tao::seq::integer_sequence< T, Ts... > )
{
   (void)std::initializer_list< int >{ ( std::cout << Ts << " ", 0 )... };
   std::cout << std::endl;
}

int main()
{
   using namespace tao::seq;

   static_assert( std::is_same< prod_t< index_sequence< 0, 5, 7, 1 >, index_sequence< 4, 5, 6, 7 > >,
                                index_sequence< 0, 25, 42, 7 > >::value,
                  "ooops" );
}
