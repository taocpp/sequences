
// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_FILTER_HPP
#define TAO_SEQ_FILTER_HPP

#include "concatenate.hpp"
#include "contains.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename, typename, typename >
         struct filter_out_seq;

         template< typename T, T... As >
         struct filter_out_seq< T, integer_sequence< T, As... >, integer_sequence< T > >
         {
            using type = integer_sequence< T >;
         };

         template< typename T, T... As, T b, T... Bs >
         struct filter_out_seq< T, integer_sequence< T, As... >, integer_sequence< T, b, Bs... > >
         {
            constexpr static bool included = tao::seq::contains< T, b, As... >::value;
            using tail = typename filter_out_seq< T, integer_sequence< T, As... >, integer_sequence< T, Bs... > >::type;
            using type = typename std::conditional<
               included,
               tail,
               typename tao::seq::concatenate< integer_sequence< T, b >, tail >::type >::type;
         };

      }  // namespace impl

      template< typename, typename >
      struct filter_out_seq;

      template< typename T, T... As, T... Bs >
      struct filter_out_seq< integer_sequence< T, As... >, integer_sequence< T, Bs... > >
      {
         using type = typename impl::filter_out_seq< T, integer_sequence< T, As... >, integer_sequence< T, Bs... > >::type;
      };

      template< typename A, typename B >
      using filter_out_seq_t = typename filter_out_seq< A, B >::type;

   }  // namespace seq
}  // namespace tao

#endif