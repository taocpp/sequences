// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_INDEX_OF_SEQ_HPP
#define TAO_SEQ_INDEX_OF_SEQ_HPP

#include "index_of.hpp"
#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename, typename, typename >
         struct index_of_seq;

         template< typename T, T... As, T... Bs >
         struct index_of_seq< T, integer_sequence< T, As... >, integer_sequence< T, Bs... > >
         {
            using type = index_sequence< tao::seq::index_of< T, Bs, As... >::value... >;
         };

      }  // namespace impl

      template< typename As, typename Bs >
      struct index_of_seq
      {
         using CT = typename std::common_type< typename impl::element_type< As >::type, typename impl::element_type< Bs >::type >::type;
         using type = typename impl::index_of_seq< CT, As, Bs >::type;
      };

      template< typename As, typename Bs >
      using index_of_seq_t = typename index_of_seq< As, Bs >::type;

   }  // namespace seq

}  // namespace tao

#endif