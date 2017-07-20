// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_VALUES_HPP
#define TAOCPP_SEQUENCES_INCLUDE_VALUES_HPP

namespace tao
{
   namespace seq
   {
      template< typename T, T... Ns >
      struct values
      {
         static constexpr T data[] = { Ns... };
      };
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_VALUES_HPP
