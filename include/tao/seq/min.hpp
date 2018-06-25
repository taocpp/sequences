// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_MIN_HPP
#define TAO_SEQ_MIN_HPP

#include "fold.hpp"

#include <type_traits>

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         struct min
         {
            template< typename T, T A, T B >
            using apply = std::integral_constant< T, ( ( A < B ) ? A : B ) >;
         };

      }  // namespace impl

      template< typename T, T... Ns >
      struct min
         : fold< impl::min, T, Ns... >
      {
      };

      template< typename T, T... Ns >
      struct min< integer_sequence< T, Ns... > >
         : min< T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
