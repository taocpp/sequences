// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PERMUTE_HPP
#define TAO_SEQ_PERMUTE_HPP

#include "index_of_seq.hpp"
#include "make_integer_sequence.hpp"
#include "map.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
      template< typename I, typename S >
      using permutate = map< index_of_seq_t< I, make_index_sequence< impl::sequence_size< S >::value > >, S >;

      template< typename S, typename M >
      using permutate_t = typename permutate< S, M >::type;

   }  // namespace seq

}  // namespace tao

#endif
