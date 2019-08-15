// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_MULTIPLY_HPP
#define TAO_SEQ_MULTIPLY_HPP

#include <type_traits>

#include "zip.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         struct multiply
         {
            template< typename T, T A, T B >
            using apply = std::integral_constant< T, A * B >;
         };

      }  // namespace impl

      template< typename A, typename B >
      using multiply = zip< impl::multiply, A, B >;

      template< typename A, typename B >
      using multiply_t = typename multiply< A, B >::type;

   }  // namespace seq

}  // namespace tao

#endif
