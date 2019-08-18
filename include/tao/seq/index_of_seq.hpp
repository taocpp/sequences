// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_INDEX_OF_SEQ_HPP
#define TAO_SEQ_INDEX_OF_SEQ_HPP

#include <type_traits>

#include "index_of.hpp"
#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      template< typename, typename >
      struct index_of_seq;

      template< typename TA, TA... As, typename TB, TB... Bs >
      struct index_of_seq< integer_sequence< TA, As... >, integer_sequence< TB, Bs... > >
      {
         using type = index_sequence< index_of< typename std::common_type< TA, TB >::type, Bs, As... >::value... >;
      };

      template< typename A, typename B >
      using index_of_seq_t = typename index_of_seq< A, B >::type;

   }  // namespace seq

}  // namespace tao

#endif
