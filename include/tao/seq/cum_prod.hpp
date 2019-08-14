// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_CUM_PROD_HPP
#define TAO_SEQ_CUM_PROD_HPP

#include "concatenate.hpp"
#include "prod_red.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename, typename >
         struct cum_prod;

         template< typename T >
         struct cum_prod< T, integer_sequence< T > >
         {
            using type = integer_sequence< T >;
         };

         template< typename T, T a, T... X >
         struct cum_prod< T, integer_sequence< T, a, X... > >
         {
            using type = typename tao::seq::concatenate<
               index_sequence< prod_red_t< integer_sequence< T, X... > >::value >,
               typename cum_prod< T, integer_sequence< T, X... > >::type >::type;
         };

      }  // namespace impl

      template< typename >
      struct cum_prod;

      template< typename T, T... X >
      struct cum_prod< integer_sequence< T, X... > >
      {
         using type = typename impl::cum_prod< T, integer_sequence< T, X... > >::type;
      };

      template< typename X >
      using cum_prod_t = typename cum_prod< X >::type;

   }  // namespace seq
}  // namespace tao

#endif