// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_FOLD_HPP
#define TAO_SEQ_FOLD_HPP

#include <type_traits>

#include "config.hpp"

#ifdef TAO_SEQ_FOLD_EXPRESSIONS

#include "integer_sequence.hpp"

#else

#include <cstddef>

#include "make_integer_sequence.hpp"
#include "select.hpp"

#endif

namespace tao
{
   namespace seq
   {

#ifdef TAO_SEQ_FOLD_EXPRESSIONS

      namespace impl
      {
         template< typename OP, typename T, T N >
         struct wrap_fold
         {
         };

         template< typename OP, typename T, T R, T L >
         constexpr auto operator+( std::integral_constant< T, R >, wrap_fold< OP, T, L > ) noexcept
         {
            return typename OP::template apply< T, R, L >();
         }

         template< typename OP, typename T, T N, T... Ns >
         constexpr auto fold() noexcept
         {
            return ( std::integral_constant< T, N >() + ... + wrap_fold< OP, T, Ns >() );
         }

      }  // namespace impl

      template< typename OP, typename T, T... Ns >
      struct fold
         : decltype( impl::fold< OP, T, Ns... >() )
      {
      };

#else

      namespace impl
      {
         template< typename OP, bool, typename, typename T, T... >
         struct folder;

         template< typename OP, std::size_t... Is, typename T, T... Ns >
         struct folder< OP, false, index_sequence< Is... >, T, Ns... >
         {
            template< std::size_t I >
            using subsel = seq::select< I, T, Ns... >;

            using type = integer_sequence< T, OP::template apply< T, subsel< 2 * Is >::value, subsel< 2 * Is + 1 >::value >::value... >;
         };

         template< typename OP, std::size_t... Is, typename T, T N, T... Ns >
         struct folder< OP, true, index_sequence< Is... >, T, N, Ns... >
         {
            template< std::size_t I >
            using subsel = seq::select< I, T, Ns... >;

            using type = integer_sequence< T, N, OP::template apply< T, subsel< 2 * Is >::value, subsel< 2 * Is + 1 >::value >::value... >;
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

#endif

      template< typename OP, typename T, T... Ns >
      struct fold< OP, integer_sequence< T, Ns... > >
         : fold< OP, T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
