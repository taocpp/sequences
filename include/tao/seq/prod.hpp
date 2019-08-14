// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PROD_HPP
#define TAO_SEQ_PROD_HPP

#include "zip.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {

         struct prod
         {
            template< typename T, T A, T B >
            using apply = std::integral_constant< T, A * B >;
         };
      }  // namespace impl

      template< typename A, typename B >
      using prod = zip< impl::prod, A, B >;

      template< typename A, typename B >
      using prod_t = typename prod< A, B >::type;

   }  // namespace seq
}  // namespace tao

#endif