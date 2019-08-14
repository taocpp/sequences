// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PROD_RED_HPP
#define TAO_SEQ_PROD_RED_HPP

#include "fold.hpp"
#include "integer_sequence.hpp"
#include "prod.hpp"

namespace tao
{
   namespace seq
   {
      template< typename >
      struct prod_red;

      template< typename T >
      struct prod_red< integer_sequence< T > >
      {
         using type = typename std::integral_constant< T, 1 >::type;
      };

      template< typename T, T... Ns >
      struct prod_red< integer_sequence< T, Ns... > >
      {
         using type = typename fold< impl::prod, T, Ns... >::type;
      };

      template< typename Ns >
      using prod_red_t = typename prod_red< Ns >::type;

   }  // namespace seq
}  // namespace tao

#endif