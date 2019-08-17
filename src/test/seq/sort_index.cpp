// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/sort_index.hpp>

#include <type_traits>

struct less
{
   template< typename T, T A, T B >
   using apply = std::integral_constant< bool, ( A < B ) >;
};

int main()
{
   using namespace tao::seq;

   using S = integer_sequence< int, 39, 2, -4, 10 >;
   using R = index_sequence< 3, 1, 0, 2 >;

   static_assert( std::is_same< sort_index_t< less, S >, R >::value, "oops" );

   static_assert( std::is_same< sort_index_t< less, int, 39, 2, -4, 10 >, R >::value, "oops" );
}
