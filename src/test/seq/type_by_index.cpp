// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/type_by_index.hpp>

#include <type_traits>

int main()
{
  using namespace tao::seq;

  static_assert( std::is_same< type_by_index_t< 0, void >, void >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, void* >, void* >::value, "oops" );

  static_assert( std::is_same< type_by_index_t< 0, int >, int >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, int* >, int* >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, int& >, int& >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, int&& >, int&& >::value, "oops" );

  static_assert( std::is_same< type_by_index_t< 0, const int >, const int >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, const int* >, const int* >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, const int& >, const int& >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 0, const int&& >, const int&& >::value, "oops" );

  static_assert( std::is_same< type_by_index_t< 0, int( long, double ) >, int( long, double ) >::value, "oops" );

  static_assert( !std::is_same< type_by_index_t< 0, void, int >, int >::value, "oops" );
  static_assert( std::is_same< type_by_index_t< 1, void, int >, int >::value, "oops" );

  static_assert( !std::is_same< type_by_index_t< 53,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, void, void, void, void,
                 void, void, void, void, long, void, void, void >, long >::value, "oops" );
}
