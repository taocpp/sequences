// Copyright (c) 2015-2018 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_IS_ALL_HPP
#define TAO_SEQ_IS_ALL_HPP

#include "config.hpp"

#ifndef TAO_SEQ_FOLD_EXPRESSIONS
#include "integer_sequence.hpp"
#endif

#include <type_traits>

namespace tao
{
   namespace seq
   {

#ifdef TAO_SEQ_FOLD_EXPRESSIONS

      template< bool... Bs >
      using is_all = std::integral_constant< bool, ( Bs && ... ) >;

#else

      template< bool... Bs >
      using is_all = std::integral_constant< bool, std::is_same< integer_sequence< bool, true, Bs... >, integer_sequence< bool, Bs..., true > >::value >;

#endif

   }  // namespace seq

}  // namespace tao

#endif
