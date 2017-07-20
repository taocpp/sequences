// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP

#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename T, T... >
         struct element_type
         {
            using type = T;
         };

         template< typename T, T... Ns >
         struct element_type< integer_sequence< T, Ns... > >
         {
            using type = T;
         };
      }

      template< typename T, typename impl::element_type< T >::type S, T... Ns >
      struct scale
      {
         using type = integer_sequence< T, S * Ns... >;
      };

      template< typename T, T S, T... Ns >
      struct scale< integer_sequence< T, Ns... >, S >
      {
         using type = integer_sequence< T, S * Ns... >;
      };

      template< typename T, typename impl::element_type< T >::type S, T... Ns >
      using scale_t = typename scale< T, S, Ns... >::type;
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
