// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_CONCATENATE_HPP
#define TAO_SEQ_CONCATENATE_HPP

#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      template< typename... >
      struct concatenate;

      template< typename T, T... Ns >
      struct concatenate< integer_sequence< T, Ns... > >
      {
         using type = integer_sequence< T, Ns... >;
      };

      template< typename TA, TA... As, typename TB, TB... Bs, typename... Ts >
      struct concatenate< integer_sequence< TA, As... >, integer_sequence< TB, Bs... >, Ts... >
         : concatenate< integer_sequence< typename std::common_type< TA, TB >::type, As..., Bs... >, Ts... >
      {
      };

      template< typename... Ts >
      using concatenate_t = typename concatenate< Ts... >::type;

   }  // namespace seq

}  // namespace tao

#endif
