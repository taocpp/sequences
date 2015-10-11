// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP
#define TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP

#include <cstddef>
#include <type_traits>

namespace tao
{
  namespace seq
  {
    namespace impl
    {
      // This is not very elegant, but it works and has O(log N) instantiation depth

      template< std::size_t, typename, typename... >
      struct type_by_index;

      template< typename T, typename... Ts >
      struct type_by_index< 0, void, T, Ts... >
      {
        using type = T;
      };

      template< std::size_t I, typename T0, typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( I == 1 ) >::type, T0, Ts... >
        : type_by_index< I - 1, void, Ts... >
      {};

      template< std::size_t I, typename T0, typename T1, typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 2 ) && ( I < 4 ) ) >::type, T0, T1, Ts... >
        : type_by_index< I - 2, void, Ts... >
      {};

      template< std::size_t I, typename T0, typename T1, typename T2, typename T3, typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 4 ) && ( I < 8 ) ) >::type, T0, T1, T2, T3, Ts... >
        : type_by_index< I - 4, void, Ts... >
      {};

      template< std::size_t I, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 8 ) && ( I < 16 ) ) >::type, T0, T1, T2, T3, T4, T5, T6, T7, Ts... >
        : type_by_index< I - 8, void, Ts... >
      {};

#define TAOCPP_HEXPAND(X) X##0, X##1, X##2, X##3, X##4, X##5, X##6, X##7, X##8, X##9, X##a, X##b, X##c, X##d, X##e, X##f

      template< std::size_t I, TAOCPP_HEXPAND(typename T0), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 16 ) && ( I < 32 ) ) >::type, TAOCPP_HEXPAND(T0), Ts... >
        : type_by_index< I - 16, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND(typename T0), TAOCPP_HEXPAND(typename T1), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 32 ) && ( I < 64 ) ) >::type, TAOCPP_HEXPAND(T0), TAOCPP_HEXPAND(T1), Ts... >
        : type_by_index< I - 32, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND(typename T0), TAOCPP_HEXPAND(typename T1), TAOCPP_HEXPAND(typename T2), TAOCPP_HEXPAND(typename T3), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 64 ) && ( I < 128 ) ) >::type, TAOCPP_HEXPAND(T0), TAOCPP_HEXPAND(T1), TAOCPP_HEXPAND(T2), TAOCPP_HEXPAND(T3), Ts... >
        : type_by_index< I - 64, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND(typename T0), TAOCPP_HEXPAND(typename T1), TAOCPP_HEXPAND(typename T2), TAOCPP_HEXPAND(typename T3), TAOCPP_HEXPAND(typename T4), TAOCPP_HEXPAND(typename T5), TAOCPP_HEXPAND(typename T6), TAOCPP_HEXPAND(typename T7), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 128 ) && ( I < 256 ) ) >::type, TAOCPP_HEXPAND(T0), TAOCPP_HEXPAND(T1), TAOCPP_HEXPAND(T2), TAOCPP_HEXPAND(T3), TAOCPP_HEXPAND(T4), TAOCPP_HEXPAND(T5), TAOCPP_HEXPAND(T6), TAOCPP_HEXPAND(T7), Ts... >
        : type_by_index< I - 128, void, Ts... >
      {};

#define TAOCPP_HEXPAND2(X) TAOCPP_HEXPAND(X)

      template< std::size_t I, TAOCPP_HEXPAND2(typename T0), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 256 ) && ( I < 512 ) ) >::type, TAOCPP_HEXPAND2(T0), Ts... >
        : type_by_index< I - 256, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND2(typename T0), TAOCPP_HEXPAND2(typename T1), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 512 ) && ( I < 1024 ) ) >::type, TAOCPP_HEXPAND2(T0), TAOCPP_HEXPAND2(T1), Ts... >
        : type_by_index< I - 512, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND2(typename T0), TAOCPP_HEXPAND2(typename T1), TAOCPP_HEXPAND2(typename T2), TAOCPP_HEXPAND2(typename T3), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 1024 ) && ( I < 2048 ) ) >::type, TAOCPP_HEXPAND2(T0), TAOCPP_HEXPAND2(T1), TAOCPP_HEXPAND2(T2), TAOCPP_HEXPAND2(T3), Ts... >
        : type_by_index< I - 1024, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND2(typename T0), TAOCPP_HEXPAND2(typename T1), TAOCPP_HEXPAND2(typename T2), TAOCPP_HEXPAND2(typename T3), TAOCPP_HEXPAND2(typename T4), TAOCPP_HEXPAND2(typename T5), TAOCPP_HEXPAND2(typename T6), TAOCPP_HEXPAND2(typename T7), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 2048 ) && ( I < 4096 ) ) >::type, TAOCPP_HEXPAND2(T0), TAOCPP_HEXPAND2(T1), TAOCPP_HEXPAND2(T2), TAOCPP_HEXPAND2(T3), TAOCPP_HEXPAND2(T4), TAOCPP_HEXPAND2(T5), TAOCPP_HEXPAND2(T6), TAOCPP_HEXPAND2(T7), Ts... >
        : type_by_index< I - 2048, void, Ts... >
      {};

#define TAOCPP_HEXPAND3(X) TAOCPP_HEXPAND2(X)

      template< std::size_t I, TAOCPP_HEXPAND3(typename T0), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x1000 ) && ( I < 0x2000 ) ) >::type, TAOCPP_HEXPAND3(T0), Ts... >
        : type_by_index< I - 0x1000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND3(typename T0), TAOCPP_HEXPAND3(typename T1), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x2000 ) && ( I < 0x4000 ) ) >::type, TAOCPP_HEXPAND3(T0), TAOCPP_HEXPAND3(T1), Ts... >
        : type_by_index< I - 0x2000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND3(typename T0), TAOCPP_HEXPAND3(typename T1), TAOCPP_HEXPAND3(typename T2), TAOCPP_HEXPAND3(typename T3), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x4000 ) && ( I < 0x8000 ) ) >::type, TAOCPP_HEXPAND3(T0), TAOCPP_HEXPAND3(T1), TAOCPP_HEXPAND3(T2), TAOCPP_HEXPAND3(T3), Ts... >
        : type_by_index< I - 0x4000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND3(typename T0), TAOCPP_HEXPAND3(typename T1), TAOCPP_HEXPAND3(typename T2), TAOCPP_HEXPAND3(typename T3), TAOCPP_HEXPAND3(typename T4), TAOCPP_HEXPAND3(typename T5), TAOCPP_HEXPAND3(typename T6), TAOCPP_HEXPAND3(typename T7), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x8000 ) && ( I < 0x10000 ) ) >::type, TAOCPP_HEXPAND3(T0), TAOCPP_HEXPAND3(T1), TAOCPP_HEXPAND3(T2), TAOCPP_HEXPAND3(T3), TAOCPP_HEXPAND3(T4), TAOCPP_HEXPAND3(T5), TAOCPP_HEXPAND3(T6), TAOCPP_HEXPAND3(T7), Ts... >
        : type_by_index< I - 0x8000, void, Ts... >
      {};

#define TAOCPP_HEXPAND4(X) TAOCPP_HEXPAND3(X)

      template< std::size_t I, TAOCPP_HEXPAND4(typename T0), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x10000 ) && ( I < 0x20000 ) ) >::type, TAOCPP_HEXPAND4(T0), Ts... >
        : type_by_index< I - 0x10000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND4(typename T0), TAOCPP_HEXPAND4(typename T1), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x20000 ) && ( I < 0x40000 ) ) >::type, TAOCPP_HEXPAND4(T0), TAOCPP_HEXPAND4(T1), Ts... >
        : type_by_index< I - 0x20000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND4(typename T0), TAOCPP_HEXPAND4(typename T1), TAOCPP_HEXPAND4(typename T2), TAOCPP_HEXPAND4(typename T3), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x40000 ) && ( I < 0x80000 ) ) >::type, TAOCPP_HEXPAND4(T0), TAOCPP_HEXPAND4(T1), TAOCPP_HEXPAND4(T2), TAOCPP_HEXPAND4(T3), Ts... >
        : type_by_index< I - 0x40000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND4(typename T0), TAOCPP_HEXPAND4(typename T1), TAOCPP_HEXPAND4(typename T2), TAOCPP_HEXPAND4(typename T3), TAOCPP_HEXPAND4(typename T4), TAOCPP_HEXPAND4(typename T5), TAOCPP_HEXPAND4(typename T6), TAOCPP_HEXPAND4(typename T7), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x80000 ) && ( I < 0x100000 ) ) >::type, TAOCPP_HEXPAND4(T0), TAOCPP_HEXPAND4(T1), TAOCPP_HEXPAND4(T2), TAOCPP_HEXPAND4(T3), TAOCPP_HEXPAND4(T4), TAOCPP_HEXPAND4(T5), TAOCPP_HEXPAND4(T6), TAOCPP_HEXPAND4(T7), Ts... >
        : type_by_index< I - 0x80000, void, Ts... >
      {};

#define TAOCPP_HEXPAND5(X) TAOCPP_HEXPAND4(X)

      template< std::size_t I, TAOCPP_HEXPAND5(typename T0), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x100000 ) && ( I < 0x200000 ) ) >::type, TAOCPP_HEXPAND5(T0), Ts... >
        : type_by_index< I - 0x100000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND5(typename T0), TAOCPP_HEXPAND5(typename T1), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x200000 ) && ( I < 0x400000 ) ) >::type, TAOCPP_HEXPAND5(T0), TAOCPP_HEXPAND5(T1), Ts... >
        : type_by_index< I - 0x200000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND5(typename T0), TAOCPP_HEXPAND5(typename T1), TAOCPP_HEXPAND5(typename T2), TAOCPP_HEXPAND5(typename T3), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( ( I >= 0x400000 ) && ( I < 0x800000 ) ) >::type, TAOCPP_HEXPAND5(T0), TAOCPP_HEXPAND5(T1), TAOCPP_HEXPAND5(T2), TAOCPP_HEXPAND5(T3), Ts... >
        : type_by_index< I - 0x400000, void, Ts... >
      {};

      template< std::size_t I, TAOCPP_HEXPAND5(typename T0), TAOCPP_HEXPAND5(typename T1), TAOCPP_HEXPAND5(typename T2), TAOCPP_HEXPAND5(typename T3), TAOCPP_HEXPAND5(typename T4), TAOCPP_HEXPAND5(typename T5), TAOCPP_HEXPAND5(typename T6), TAOCPP_HEXPAND5(typename T7), typename... Ts>
      struct type_by_index< I, typename std::enable_if< ( I >= 0x800000 ) >::type, TAOCPP_HEXPAND5(T0), TAOCPP_HEXPAND5(T1), TAOCPP_HEXPAND5(T2), TAOCPP_HEXPAND5(T3), TAOCPP_HEXPAND5(T4), TAOCPP_HEXPAND5(T5), TAOCPP_HEXPAND5(T6), TAOCPP_HEXPAND5(T7), Ts... >
        : type_by_index< I - 0x800000, void, Ts... >
      {};

#undef TAOCPP_HEXPAND5
#undef TAOCPP_HEXPAND4
#undef TAOCPP_HEXPAND3
#undef TAOCPP_HEXPAND2
#undef TAOCPP_HEXPAND

    }

    template< std::size_t I, typename... Ts >
    using type_by_index = impl::type_by_index< I, void, Ts... >;

    template< std::size_t I, typename... Ts >
    using type_by_index_t = typename type_by_index< I, Ts... >::type;
  }
}

#endif // TAOCPP_SEQUENCES_INCLUDE_TYPE_BY_INDEX_HPP
