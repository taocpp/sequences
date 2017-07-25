// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP
#define TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP

#if __cplusplus >= 201402L
#define TAOCPP_USE_STD_INTEGER_SEQUENCE
#endif

#if defined( _LIBCPP_VERSION ) && ( __cplusplus >= 201402L )
#define TAOCPP_USE_STD_MAKE_INTEGER_SEQUENCE
#endif

#if defined( _MSC_VER ) && ( _MSC_VER >= 190023918 )
#define TAOCPP_USE_STD_MAKE_INTEGER_SEQUENCE
#endif

#if defined( __cpp_fold_expressions )
#define TAOCPP_FOLD_EXPRESSIONS
#endif

#endif  // TAOCPP_SEQUENCES_INCLUDE_CONFIG_HPP
