// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/integer_sequence.hpp>
#include <tao/seq/prod_red.hpp>

int main()
{
   using namespace tao::seq;

   static_assert( prod_red_t< integer_sequence< int, -1, 4, 5 > >::value == -20, "ooops" );
}
