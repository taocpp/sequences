// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PARTIAL_FOLD_HPP
#define TAO_SEQ_PARTIAL_FOLD_HPP

#include <cstddef>

#include "fold.hpp"
#include "make_integer_sequence.hpp"
#include "select.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename OP, typename I, typename T, T... Ns >
         struct partial_fold;

         template< typename OP, std::size_t... Is, typename T, T... Ns >
         struct partial_fold< OP, index_sequence< Is... >, T, Ns... >
         {
            template< std::size_t I >
            using element = seq::select< I, T, Ns... >;

            using type = seq::fold< OP, T, element< Is >::value... >;
         };

      }  // namespace impl

      template< typename OP, std::size_t I, typename T, T... Ns >
      struct partial_fold
         : impl::partial_fold< OP, make_index_sequence< I >, T, Ns... >::type
      {
      };

      template< typename OP, std::size_t I, typename T, T... Ns >
      struct partial_fold< OP, I, integer_sequence< T, Ns... > >
         : partial_fold< OP, I, T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
