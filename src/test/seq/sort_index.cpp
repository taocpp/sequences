// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/sort_index.hpp>

template< class T, T a, T b >
struct ord
{
   static const bool value = a < b;
};

template< int a, int b >
using ord_int = ord< int, a, b >;

template< size_t a, size_t b >
using ord_st = ord< size_t, a, b >;

int main()
{
   using namespace tao::seq;

   using U = index_sequence< 39, 2, 4, 10 >;

   static_assert( std::is_same< tao::seq::sort_index_t< U, ord_st >, index_sequence< 3, 0, 1, 2 > >::value, "ooops" );
}
