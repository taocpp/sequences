// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_TYPE_BY_INDEX_HPP
#define TAO_SEQ_TYPE_BY_INDEX_HPP

#include <cstddef>
#include <type_traits>

#include "make_integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template< typename T >
         struct identity
         {
            using type = T;
         };

         template< std::size_t, typename T >
         struct indexed_type
         {
            using type = T;
         };

         template< typename, typename... >
         struct type_union;

         template< std::size_t... Is, typename... Ts >
         struct type_union< index_sequence< Is... >, Ts... >
            : indexed_type< Is, Ts >...
         {
         };

         template< std::size_t I, typename T >
         identity< T > select_type( const indexed_type< I, T >& );

      }  // namespace impl

      template< std::size_t I, typename... Ts >
      using type_by_index = decltype( impl::select_type< I >( impl::type_union< index_sequence_for< Ts... >, Ts... >{} ) );

      template< std::size_t I, typename... Ts >
      using type_by_index_t = typename type_by_index< I, Ts... >::type;

   }  // namespace seq

}  // namespace tao

#endif
