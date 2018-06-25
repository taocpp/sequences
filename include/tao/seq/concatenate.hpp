// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_CONCATENATE_HPP
#define TAO_SEQ_CONCATENATE_HPP

#include <type_traits>

#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      template< typename, typename >
      struct concatenate;

      template< typename TA, TA... As, typename TB, TB... Bs >
      struct concatenate< integer_sequence< TA, As... >, integer_sequence< TB, Bs... > >
      {
         using type = integer_sequence< typename std::common_type< TA, TB >::type, As..., Bs... >;
      };

      template< typename A, typename B >
      using concatenate_t = typename concatenate< A, B >::type;

   }  // namespace seq

}  // namespace tao

#endif
