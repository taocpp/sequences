// Copyright (c) 2017 Michiel van Slobbe <mvslobbe@athenacr.com>
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_CONTAINS_HPP
#define TAOCPP_SEQUENCES_INCLUDE_CONTAINS_HPP

#include <type_traits>
#include <utility>

#include "config.hpp"
#include "integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      namespace impl
      {
         template<typename T, typename T::value_type val>
         struct contains {};

         template<typename T, T N, T val>
         struct contains<integer_sequence<T, N>, val>
         {
             static const bool value = ( val == N );
         };

         template<typename T, T N, T... Ns, T val>
         struct contains<integer_sequence<T, N, Ns...>, val>
         {
            static const bool value = ( val == N || contains<integer_sequence<T, Ns...>, val>::value );
         };
      }

      template<typename T, typename T::value_type N>
      using contains = impl::contains<T, N>;
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_CONTAINS_HPP
