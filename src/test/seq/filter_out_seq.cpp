// Copyright (c) 2019 François-David Collin
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#include <tao/seq/filter_out_seq.hpp>
#include <tao/seq/integer_sequence.hpp>

int main()
{
   using namespace tao::seq;

   static_assert( std::is_same< filter_out_seq_t< index_sequence< 4, 6 >, index_sequence< 4, 5, 6, 7 > >,
                                index_sequence< 5, 7 > >::value,
                  "ooops" );
}
