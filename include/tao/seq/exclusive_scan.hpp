// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_EXCLUSIVE_SCAN_HPP
#define TAO_SEQ_EXCLUSIVE_SCAN_HPP

#include <type_traits>

#include "integer_sequence.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
#if( __cplusplus >= 201402L )

      namespace impl
      {
         template< typename OP, typename T, T... Ns, T V >
         constexpr auto exclusive_scan( integer_sequence< T, Ns... >, std::integral_constant< T, V >, integer_sequence< T > ) noexcept
         {
            return integer_sequence< T, Ns... >();
         }

         template< typename OP, typename T, T... Ns, T V, T R, T... Rs >
         constexpr auto exclusive_scan( integer_sequence< T, Ns... >, std::integral_constant< T, V >, integer_sequence< T, R, Rs... > ) noexcept
         {
            return exclusive_scan< OP, T >( integer_sequence< T, Ns..., V >(), typename OP::template apply< T, V, R >(), integer_sequence< T, Rs... >() );
         }

      }  // namespace impl

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      struct exclusive_scan
      {
         using type = decltype( impl::exclusive_scan< OP, T >( integer_sequence< T >(), std::integral_constant< T, Init >(), integer_sequence< T, Ns... >() ) );
      };

#else

      namespace impl
      {
         template< typename, typename T, typename, T, typename >
         struct exclusive_scan;

         template< typename OP, typename T, T... Ns, T V >
         struct exclusive_scan< OP, T, integer_sequence< T, Ns... >, V, integer_sequence< T > >
         {
            using type = integer_sequence< T, Ns... >;
         };

         template< typename OP, typename T, T... Ns, T V, T R, T... Rs >
         struct exclusive_scan< OP, T, integer_sequence< T, Ns... >, V, integer_sequence< T, R, Rs... > >
            : exclusive_scan< OP, T, integer_sequence< T, Ns..., V >, OP::template apply< T, V, R >::value, integer_sequence< T, Rs... > >
         {
         };

      }  // namespace impl

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      struct exclusive_scan
         : impl::exclusive_scan< OP, T, integer_sequence< T >, Init, integer_sequence< T, Ns... > >
      {
      };

#endif

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      struct exclusive_scan< OP, integer_sequence< T, Ns... >, Init >
         : exclusive_scan< OP, T, Init, Ns... >
      {
      };

      template< typename OP, typename T, typename impl::element_type< T >::type Init, T... Ns >
      using exclusive_scan_t = typename exclusive_scan< OP, T, Init, Ns... >::type;

   }  // namespace seq

}  // namespace tao

#endif
