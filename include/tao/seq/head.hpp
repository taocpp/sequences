// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_HEAD_HPP
#define TAOCPP_SEQUENCES_INCLUDE_HEAD_HPP

#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      template< typename T, T... Ns >
      struct head;

      template< typename T, T N, T... Ns >
      struct head< T, N, Ns... >
         : std::integral_constant< T, N >
      {
      };

      template< typename T, T... Ns >
      struct head< integer_sequence< T, Ns... > >
         : head< T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
