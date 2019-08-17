// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_SORT_HPP
#define TAO_SEQ_SORT_HPP

#include <type_traits>

#include "integer_sequence.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename OP, typename T, T V, typename S, typename R >
         struct insert;

         template< typename OP, typename T, T V, T... Rs >
         struct insert< OP, T, V, integer_sequence< T >, integer_sequence< T, Rs... > >
         {
            using type = integer_sequence< T, Rs..., V >;
         };

         template< typename OP, typename T, T V, T N, T... Ns, T... Rs >
         struct insert< OP, T, V, integer_sequence< T, N, Ns... >, integer_sequence< T, Rs... > >
         {
            using type = typename conditional< OP::template apply< T, V, N >::value >::template type<
               integer_sequence< T, Rs..., V, N, Ns... >,
               typename insert< OP, T, V, integer_sequence< T, Ns... >, integer_sequence< T, Rs..., N > >::type >;
         };

         template< typename OP, typename Sorted, typename Unsorted >
         struct sort;

         template< typename OP, typename T, T... Ns >
         struct sort< OP, integer_sequence< T, Ns... >, integer_sequence< T > >
         {
            using type = integer_sequence< T, Ns... >;
         };

         template< typename OP, typename T, T... Ns, T V, T... Rs >
         struct sort< OP, integer_sequence< T, Ns... >, integer_sequence< T, V, Rs... > >
            : sort< OP, typename insert< OP, T, V, integer_sequence< T, Ns... >, integer_sequence< T > >::type, integer_sequence< T, Rs... > >
         {
         };

      }  // namespace impl

      template< typename OP, typename T, T... Ns >
      struct sort
         : impl::sort< OP, integer_sequence< T >, integer_sequence< T, Ns... > >
      {
      };

      template< typename OP, typename T, T... Ns >
      struct sort< OP, integer_sequence< T, Ns... > >
         : sort< OP, T, Ns... >
      {
      };

      template< typename OP, typename T, typename impl::element_type< T >::type... Ns >
      using sort_t = typename sort< OP, T, Ns... >::type;

   }  // namespace seq

}  // namespace tao

#endif
