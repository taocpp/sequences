// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PERMUTE_HPP
#define TAO_SEQ_PERMUTE_HPP

#include "index_of_seq.hpp"
#include "integer_sequence.hpp"
#include "make_integer_sequence.hpp"
#include "map.hpp"

namespace tao
{
   namespace seq
   {
      template< typename, typename >
      struct permute;

      template< std::size_t... Ns, typename M >
      struct permute< index_sequence< Ns... >, M >
      {
         using tmp = index_of_seq_t< index_sequence< Ns... >, make_index_sequence< sizeof...( Ns ) > >;
         using type = typename map< tmp, M >::type;
      };

      template< typename S, typename M >
      using permute_t = typename permute< S, M >::type;

   }  // namespace seq
}  // namespace tao

#endif