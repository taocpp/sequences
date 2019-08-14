// Copyright (c) 2019 François-David Collin <fradav@gmail.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_SORT_INDEX_HPP
#define TAO_SEQ_SORT_INDEX_HPP

#include "sort.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< class T, template< T, T > class Pred, class Ns >
         struct sort_index
         {
            using sorted = typename sort< T, Pred, Ns >::type;
            using type = tao::seq::index_of_seq_t< sorted, Ns >;
         };

      }  // namespace impl

      template< class Is, template< typename impl::element_type< Is >::type, typename impl::element_type< Is >::type > class Pred >
      struct sort_index
      {
         using type = typename impl::sort_index< typename impl::element_type< Is >::type, Pred, Is >::type;
      };

      template< class Is, template< typename impl::element_type< Is >::type, typename impl::element_type< Is >::type > class Pred >
      using sort_index_t = typename impl::sort_index< typename impl::element_type< Is >::type, Pred, Is >::type;

   }  // namespace seq
}  // namespace tao

#endif