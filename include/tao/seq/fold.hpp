// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_FOLD_HPP
#define TAO_SEQ_FOLD_HPP

#include <type_traits>

#include "integer_sequence.hpp"
#include "make_integer_sequence.hpp"
#include "select.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename OP, bool, typename, typename T, T... >
         struct folder;

         template< typename OP, std::size_t... Is, typename T, T... Ns >
         struct folder< OP, false, index_sequence< Is... >, T, Ns... >
         {
            using type = integer_sequence< T, OP::template apply< T, seq::select< 2 * Is, T, Ns... >::value, seq::select< 2 * Is + 1, T, Ns... >::value >::value... >;
         };

         template< typename OP, std::size_t... Is, typename T, T N, T... Ns >
         struct folder< OP, true, index_sequence< Is... >, T, N, Ns... >
         {
            using type = integer_sequence< T, N, OP::template apply< T, seq::select< 2 * Is, T, Ns... >::value, seq::select< 2 * Is + 1, T, Ns... >::value >::value... >;
         };

      }  // namespace impl

      template< typename, typename T, T... >
      struct fold;

      template< typename OP, typename T, T N >
      struct fold< OP, T, N >
         : std::integral_constant< T, N >
      {
      };

      template< typename OP, typename T, T... Ns >
      struct fold
         : fold< OP, typename impl::folder< OP, sizeof...( Ns ) % 2 == 1, make_index_sequence< sizeof...( Ns ) / 2 >, T, Ns... >::type >
      {
      };

      template< typename OP, typename T, T... Ns >
      struct fold< OP, integer_sequence< T, Ns... > >
         : fold< OP, T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
