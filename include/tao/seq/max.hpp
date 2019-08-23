// Copyright (c) 2015-2019 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAO_SEQ_MAX_HPP
#define TAO_SEQ_MAX_HPP

#include "fold.hpp"
#include "functional.hpp"

namespace tao
{
   namespace seq
   {
      template< typename T, T... Ns >
      using max = fold< op::max, T, Ns... >;

   }  // namespace seq

}  // namespace tao

#endif
