// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_SORT_HPP
#define TAO_SEQ_SORT_HPP

#include "concatenate.hpp"
#include "index_of_seq.hpp"
#include "integer_sequence.hpp"
#include "make_integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< class T, template< T, T > class Pred, class Ia, class Ib >
         struct merge;

         template< class T, template< T, T > class Pred, class Ib >
         struct merge< T, Pred, integer_sequence< T >, Ib >
         {
            using type = Ib;
         };

         template< class T, template< T, T > class Pred, class Ia >
         struct merge< T, Pred, Ia, integer_sequence< T > >
         {
            using type = Ia;
         };

         template< class T, template< T, T > class Pred, T a, T... Ia, T b, T... Ib >
         struct merge< T, Pred, integer_sequence< T, a, Ia... >, integer_sequence< T, b, Ib... > >
         {
            using type = typename std::conditional< Pred< a, b >::value,
                                                    tao::seq::concatenate_t< integer_sequence< T, a >, typename merge< T, Pred, integer_sequence< T, Ia... >, integer_sequence< T, b, Ib... > >::type >,
                                                    tao::seq::concatenate_t< integer_sequence< T, b >, typename merge< T, Pred, integer_sequence< T, a, Ia... >, integer_sequence< T, Ib... > >::type > >::type;
         };

         template< class T, template< T, T > class Pred, class Is >
         struct sort;

         template< class T, template< T, T > class Pred, T a, T... Is >
         struct sort< T, Pred, integer_sequence< T, a, Is... > >
         {
            using tail_sorted = typename sort< T, Pred, integer_sequence< T, Is... > >::type;
            using type = typename merge< T, Pred, integer_sequence< T, a >, tail_sorted >::type;
         };

         template< class T, template< T, T > class Pred >
         struct sort< T, Pred, integer_sequence< T > >
         {
            using type = integer_sequence< T >;
         };

      }  // namespace impl

      template< class Is, template< typename impl::element_type< Is >::type, typename impl::element_type< Is >::type > class Pred >
      struct sort
      {
         using type = typename impl::sort< typename impl::element_type< Is >::type, Pred, Is >::type;
      };

      template< class Is, template< typename impl::element_type< Is >::type, typename impl::element_type< Is >::type > class Pred >
      using sort_t = typename impl::sort< typename impl::element_type< Is >::type, Pred, Is >::type;

   }  // namespace seq
}  // namespace tao

#endif