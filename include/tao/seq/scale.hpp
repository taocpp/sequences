// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP

#include "integer_sequence.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< bool, typename >
         struct scale
         {
            template< typename T, T S, T... Ns >
            struct impl
            {
               using type = integer_sequence< T, S * Ns... >;
            };
         };

         template< typename T, T... Ns >
         struct scale< true, integer_sequence< T, Ns... > >
         {
            template< typename, T S >
            struct impl
            {
               using type = integer_sequence< T, S * Ns... >;
            };
         };
      }

      template< typename T, typename impl::element_type< T >::type S, typename impl::element_type< T >::type... Ns >
      using scale = typename impl::scale< impl::is_integer_sequence< T >::value, T >::template impl< T, S, Ns... >;

      template< typename T, typename impl::element_type< T >::type S, typename impl::element_type< T >::type... Ns >
      using scale_t = typename scale< T, S, Ns... >::type;
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_SCALE_HPP
