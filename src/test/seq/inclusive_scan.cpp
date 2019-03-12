// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/inclusive_scan.hpp>
#include <tao/seq/integer_sequence.hpp>

#include <type_traits>

int main()
{
   using namespace tao::seq;

   static_assert( std::is_same< inclusive_scan_t< unsigned >, integer_sequence< unsigned > >::value, "oops" );
   static_assert( std::is_same< inclusive_scan_t< int, 2, 3, -1, 0, 4, -1, 1, 1 >, integer_sequence< int, 2, 5, 4, 4, 8, 7, 8, 9 > >::value, "oops" );
}
