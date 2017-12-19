// Copyright (c) 2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_SEQUENCE_HELPER_HPP
#define TAOCPP_SEQUENCES_INCLUDE_SEQUENCE_HELPER_HPP

#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename T >
         struct is_integer_sequence : std::false_type
         {
         };

         template< typename T, T... Ns >
         struct is_integer_sequence< integer_sequence< T, Ns... > > : std::true_type
         {
         };

         template< typename T >
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
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_SEQUENCE_HELPER_HPP
