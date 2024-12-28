// Copyright (c) 2017-2020 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_INDEX_OF_HPP
#define TAO_SEQ_INDEX_OF_HPP

#include "contains.hpp"
#include "make_integer_sequence.hpp"
#include "min.hpp"
#include "sequence_helper.hpp"

namespace tao
{
   namespace sequence
   {
      namespace impl
      {
         template< typename, typename >
         struct index_of;

         template< typename U, std::size_t... Is >
         struct index_of< U, index_sequence< Is... > >
         {
            template< typename T, T N, T... Ns >
            using type = sequence::min< std::size_t, ( ( N == Ns ) ? Is : sizeof...( Is ) )... >;
         };

         template< typename T, T... Ns, std::size_t... Is >
         struct index_of< integer_sequence< T, Ns... >, index_sequence< Is... > >
         {
            template< typename, T N >
            using type = sequence::min< std::size_t, ( ( N == Ns ) ? Is : sizeof...( Is ) )... >;
         };

      }  // namespace impl

      template< typename T, typename impl::element_type< T >::type N, T... Ns >
      struct index_of
         : impl::index_of< T, make_index_sequence< impl::sequence_size< T, Ns... >::value > >::template type< T, N, Ns... >
      {
         static_assert( contains< T, N, Ns... >::value, "index not found" );
      };

   }  // namespace sequence

}  // namespace tao

#endif
