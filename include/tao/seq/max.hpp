// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_MAX_HPP
#define TAO_SEQ_MAX_HPP

#include "fold.hpp"

#include <type_traits>

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         struct max
         {
            template< typename T, T A, T B >
            using apply = std::integral_constant< T, ( ( A > B ) ? A : B ) >;
         };

      }  // namespace impl

      template< typename T, T... Ns >
      struct max
         : fold< impl::max, T, Ns... >
      {
      };

      template< typename T, T... Ns >
      struct max< integer_sequence< T, Ns... > >
         : max< T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
