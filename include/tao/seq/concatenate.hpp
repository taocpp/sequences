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

      template< typename TA, TA... As, typename TB, TB... Bs >
      struct concatenate< integer_sequence< TA, As... >, integer_sequence< TB, Bs... > >
      {
         using type = integer_sequence< typename std::common_type< TA, TB >::type, As..., Bs... >;
      };

      template< typename... Ts >
      using concatenate_t = typename concatenate< Ts... >::type;

      // TODO: Can this recursion be improved?
      template< typename TA, typename TB, typename TC, typename... Ts >
      struct concatenate< TA, TB, TC, Ts... >
         : concatenate< concatenate_t< TA, TB >, concatenate_t< TC, Ts... > >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
