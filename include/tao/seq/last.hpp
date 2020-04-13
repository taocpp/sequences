// Copyright (c) 2019-2020 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_LAST_HPP
#define TAO_SEQ_LAST_HPP

#include <type_traits>

#include "config.hpp"

#include "integer_sequence.hpp"

#ifndef TAO_SEQ_FOLD_EXPRESSIONS
#include "at_index.hpp"
#endif

namespace tao
{
   namespace seq
   {
#ifdef TAO_SEQ_FOLD_EXPRESSIONS

      template< typename T, T... Ns >
      struct last
         : decltype( ( std::integral_constant< T, Ns >(), ... ) )
      {
      };

#else

      template< typename T, T... Ns >
      struct last
         : at_index_t< sizeof...( Ns ) - 1, std::integral_constant< T, Ns >... >
      {
      };

#endif

      template< typename T, T... Ns >
      struct last< integer_sequence< T, Ns... > >
         : last< T, Ns... >
      {
      };

      template< typename T >
      struct last< T >
         : std::integral_constant< T, 0 >
      {
         static_assert( sizeof( T ) == 0, "no elements available" );
      };

   }  // namespace seq

}  // namespace tao

#endif
