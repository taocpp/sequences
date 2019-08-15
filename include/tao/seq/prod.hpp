// Copyright (c) 2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_PROD_HPP
#define TAO_SEQ_PROD_HPP

#include <type_traits>
#include <utility>

#include "config.hpp"
#include "integer_sequence.hpp"

#ifndef TAO_SEQ_FOLD_EXPRESSIONS
#include "fold.hpp"
#include "multiply.hpp"
#endif

namespace tao
{
   namespace seq
   {

#ifdef TAO_SEQ_FOLD_EXPRESSIONS

      template< typename T, T... Ns >
      struct prod
         : std::integral_constant< T, ( Ns * ... * T( 1 ) ) >
      {
      };

#else

      template< typename T, T... Ns >
      struct prod
         : fold< impl::multiply, T, T( 1 ), Ns... >
      {
      };

#endif

      template< typename T, T... Ns >
      struct prod< integer_sequence< T, Ns... > >
         : prod< T, Ns... >
      {
      };

   }  // namespace seq

}  // namespace tao

#endif
