// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_SORT_INDEX_HPP
#define TAO_SEQ_SORT_INDEX_HPP

#include "index_of_seq.hpp"
#include "sequence_helper.hpp"
#include "sort.hpp"

namespace tao
{
   namespace seq
   {
      template< typename OP, typename T, T... Ns >
      struct sort_index
         : sort_index< OP, integer_sequence< T, Ns... > >
      {
      };

      template< typename OP, typename T, T... Ns >
      struct sort_index< OP, integer_sequence< T, Ns... > >
         : index_of_seq< sort_t< OP, T, Ns... >, integer_sequence< T, Ns... > >
      {
      };

      template< typename OP, typename T, T... Ns >
      using sort_index_t = typename sort_index< OP, T, Ns... >::type;

   }  // namespace seq

}  // namespace tao

#endif
