// The Art of C++ / Tuple
// Copyright (c) 2015 Daniel Frey

#ifndef TAOCPP_INCLUDE_TUPLE_HPP
#define TAOCPP_INCLUDE_TUPLE_HPP

#include "integer_sequence.hpp"
#include "is_all.hpp"
#include "type_by_index.hpp"
#include "sum.hpp"
#include "make_integer_sequence.hpp"
#include "inclusive_scan.hpp"
#include "minus.hpp"
#include "map.hpp"
#include "exclusive_scan.hpp"

#include <type_traits>
#include <utility>

#if (__cplusplus >= 201402L)
#define TAOCPP_TUPLE_CONSTEXPR constexpr
#else
#define TAOCPP_TUPLE_CONSTEXPR
#endif

namespace tao
{
  namespace impl
  {
    // TODO: This is a tuple reference implementation, it is known to be incomplete!

    // TODO: std::pair support
    // TODO: allocator support

    template< typename T, bool >
    struct dependent_type : T {};

    template< bool B, typename T = void >
    using enable_if_t = typename std::enable_if< B, T >::type;

    template< typename T >
    using is_nothrow_swappable = std::integral_constant< bool, noexcept( swap( std::declval< T& >(), std::declval< T& >() ) ) >;

    template< std::size_t I, typename T, bool = std::is_empty< T >::value >
    struct tuple_value
    {
      T value;

      constexpr tuple_value()
        noexcept( std::is_nothrow_default_constructible< T >::value )
        : value()
      {
        static_assert( !std::is_reference< T >::value, "attempted to default construct a reference element in a tuple" );
      }

      template< typename U,
                typename = impl::enable_if_t< !std::is_same< typename std::decay< U >::type, tuple_value >::value >,
                typename = impl::enable_if_t< std::is_constructible< T, U >::value > >
      TAOCPP_TUPLE_CONSTEXPR
      explicit tuple_value( U&& u )
        noexcept( std::is_nothrow_constructible< T, U >::value )
        : value( std::forward< U >( u ) )
      {}

      tuple_value( const tuple_value& ) = default;
      tuple_value( tuple_value&& ) = default;

      bool swap( tuple_value& v )
        noexcept( is_nothrow_swappable< T >::value )
      {
        using std::swap;
        swap( value, v.value );
        return true;
      }

      TAOCPP_TUPLE_CONSTEXPR
      T& get() noexcept
      {
        return value;
      }

      TAOCPP_TUPLE_CONSTEXPR
      const T& get() const noexcept
      {
        return value;
      }
    };

    template< std::size_t I, typename T >
    struct tuple_value< I, T, true >
      : private T
    {
      constexpr tuple_value()
        noexcept( std::is_nothrow_default_constructible< T >::value )
        : T()
      {}

      template< typename U,
                typename = impl::enable_if_t< !std::is_same< typename std::decay< U >::type, tuple_value >::value >,
                typename = impl::enable_if_t< std::is_constructible< T, U >::value > >
      TAOCPP_TUPLE_CONSTEXPR
      explicit tuple_value( U&& u )
        noexcept( std::is_nothrow_constructible< T, U >::value )
        : T( std::forward< U >( u ) )
      {}

      tuple_value( const tuple_value& ) = default;
      tuple_value( tuple_value&& ) = default;

      bool swap( tuple_value& v )
        noexcept( is_nothrow_swappable< T >::value )
      {
        using std::swap;
        swap( *this, v );
        return true;
      }

      TAOCPP_TUPLE_CONSTEXPR
      T& get() noexcept
      {
        return static_cast< T& >( *this );
      }

      TAOCPP_TUPLE_CONSTEXPR
      const T& get() const noexcept
      {
        return static_cast< const T& >( *this );
      }
    };

    template< typename, typename... >
    struct tuple_base;

    template< std::size_t... Is, typename... Ts >
    struct tuple_base< seq::index_sequence< Is... >, Ts... >
      : tuple_value< Is, Ts >...
    {
      // 20.4.2.1 Construction [tuple.cnstr]

      constexpr tuple_base() = default;

      template< typename... Us >
      TAOCPP_TUPLE_CONSTEXPR
      explicit tuple_base( Us&&... us )
        : tuple_value< Is, Ts >( std::forward< Us >( us ) )...
      {}

      tuple_base( const tuple_base& ) = default;
      tuple_base( tuple_base&& ) = default;

      TAOCPP_TUPLE_CONSTEXPR
      tuple_base& operator=( const tuple_base& ) = default;

      TAOCPP_TUPLE_CONSTEXPR
      tuple_base& operator=( tuple_base&& ) = default;

      void swap( tuple_base& v )
        noexcept( seq::is_all< impl::is_nothrow_swappable< Ts >::value... >::value )
      {
#ifdef TAOCPP_FOLD_EXPRESSIONS
        ( static_cast< tuple_value< Is, Ts >& >( *this ).swap( static_cast< tuple_value< Is, Ts >& >( v ) ) && ... );
#else
        using swallow = bool[];
        (void)swallow{ ( static_cast< tuple_value< Is, Ts >& >( *this ).swap( static_cast< tuple_value< Is, Ts >& >( v ) ) )..., true };
#endif
      }
    };
  }

  // 20.4.2 Class template tuple [tuple.tuple]

  template< typename... Ts >
  struct tuple;

  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  const seq::type_by_index_t< I, Ts... >& get( const tuple< Ts... >& ) noexcept;

  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  seq::type_by_index_t< I, Ts... >& get( tuple< Ts... >& ) noexcept;

  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  seq::type_by_index_t< I, Ts... >&& get( const tuple< Ts... >&& ) noexcept;

  // tuple
  template< typename... Ts >
  struct tuple
  {
  private:
    using base_t = impl::tuple_base< seq::index_sequence_for< Ts... >, Ts... >;
    base_t base;

    template< std::size_t I, typename... Us >
    friend TAOCPP_TUPLE_CONSTEXPR
    const seq::type_by_index_t< I, Us... >& get( const tuple< Us... >& t ) noexcept;

    template< std::size_t I, typename... Us >
    friend TAOCPP_TUPLE_CONSTEXPR
    seq::type_by_index_t< I, Us... >& get( tuple< Us... >& ) noexcept;

    template< std::size_t I, typename... Us >
    friend TAOCPP_TUPLE_CONSTEXPR
    seq::type_by_index_t< I, Us... >&& get( tuple< Us... >&& ) noexcept;

  public:
    // 20.4.2.1 Construction [tuple.cnstr]

    // TODO: Move this templated condition to base?
    template< bool dummy = true,
              typename = impl::enable_if_t< seq::is_all< impl::dependent_type< std::is_default_constructible< Ts >, dummy >::value... >::value > >
    constexpr tuple()
      noexcept( seq::is_all< std::is_nothrow_default_constructible< Ts >::value... >::value )
      : base()
    {}

    template< bool dummy = true,
              typename = impl::enable_if_t< seq::is_all< impl::dependent_type< std::is_copy_constructible< Ts >, dummy >::value... >::value > >
    TAOCPP_TUPLE_CONSTEXPR
    explicit tuple( const Ts&... ts )
      noexcept( seq::is_all< std::is_nothrow_copy_constructible< Ts >::value... >::value )
      : base( ts... )
    {}

    template< typename... Us,
              typename = impl::enable_if_t< sizeof...( Us ) == sizeof...( Ts ) >,
              typename = impl::enable_if_t< seq::is_all< std::is_constructible< Ts, Us&& >::value... >::value > >
    TAOCPP_TUPLE_CONSTEXPR
    explicit tuple( Us&&... us )
      noexcept( seq::is_all< std::is_nothrow_constructible< Ts, Us&& >::value... >::value )
      : base( std::forward< Us >( us )... )
    {}

    tuple( const tuple& ) = default;
    tuple( tuple&& ) = default;

    template< typename... Us,
              typename = impl::enable_if_t< sizeof...( Us ) == sizeof...( Ts ) >,
              typename = impl::enable_if_t< seq::is_all< std::is_constructible< Ts, const Us& >::value... >::value > >
    TAOCPP_TUPLE_CONSTEXPR
    explicit tuple( const tuple< Us... >& t )
      // TODO: ? noexcept( seq::is_all< std::is_nothrow_constructible< Ts, const Us& >::value... >::value )
      : base( t )
    {}

    template< typename... Us,
              typename = impl::enable_if_t< sizeof...( Us ) == sizeof...( Ts ) >,
              typename = impl::enable_if_t< seq::is_all< std::is_constructible< Ts, Us&& >::value... >::value > >
    TAOCPP_TUPLE_CONSTEXPR
    explicit tuple( tuple< Us... >&& t )
      // TODO: ? noexcept( seq::is_all< std::is_nothrow_constructible< Ts, Us&& >::value... >::value )
      : base( std::move( t ) )
    {}

    // 20.4.2.2 Assignment [tuple.assign]

    // TODO: Implement me!

    // 20.4.2.3 swap [tuple.swap]

    void swap( tuple& v )
      noexcept( noexcept( base.swap( v.base ) ) )
    {
      base.swap( v.base );
    }
  };

  template<>
  struct tuple<>
  {
    constexpr tuple() noexcept {}
    void swap( tuple& ) noexcept {}
  };

  // 20.4.2.4 Tuple creation functions [tuple.creation]

  // ignore helper
  namespace impl
  {
    struct ignore_t
    {
      template< typename U >
      ignore_t& operator=( U&& )
      {
        return *this;
      }
    };
  }

  // ignore
  const impl::ignore_t ignore{};

  // make_tuple helper
  namespace impl
  {
    template< typename T >
    struct make_tuple_return
    {
      using type = T;
    };

    template< typename T >
    struct make_tuple_return< std::reference_wrapper< T > >
    {
      using type = T&;
    };

    template< typename T >
    using make_tuple_return_t = typename make_tuple_return< T >::type;
  }

  // make_tuple
  template< typename... Ts, typename R = tuple< impl::make_tuple_return_t< typename std::decay< Ts >::type >... > >
  TAOCPP_TUPLE_CONSTEXPR
  R make_tuple( Ts&&... ts )
  {
    return R( std::forward< Ts >( ts )... );
  }

  // forward_as_tuple
  template< typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  tuple< Ts&&... > forward_as_tuple( Ts&&... ts ) noexcept
  {
    return tuple< Ts&&... >( std::forward< Ts >( ts )... );
  }

  // tie
  template< typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  tuple< Ts&... > tie( Ts&... ts ) noexcept
  {
    return tuple< Ts&... >( ts... );
  }

  // tuple_cat is found at the end, as it requires access to tuple_element_t and get<I>

  // 20.4.2.5 Tuple helper classes [tuple.helper]

  // tuple_size
  template< typename T > struct tuple_size;
  template< typename T > struct tuple_size< const T > : tuple_size< T > {};
  template< typename T > struct tuple_size< volatile T > : tuple_size< T > {};
  template< typename T > struct tuple_size< const volatile T > : tuple_size< T > {};

  template< typename... Ts >
  struct tuple_size< tuple< Ts... > >
    : std::integral_constant< std::size_t, sizeof...( Ts ) >
  {};

  // tuple_element
  template< std::size_t I, typename T > struct tuple_element;
  template< std::size_t I, typename T > struct tuple_element< I, const T > : tuple_element< I, T > {};
  template< std::size_t I, typename T > struct tuple_element< I, volatile T > : tuple_element< I, T > {};
  template< std::size_t I, typename T > struct tuple_element< I, const volatile T > : tuple_element< I, T > {};

  template< std::size_t I, typename... Ts >
  struct tuple_element< I, tuple< Ts... > >
    : seq::type_by_index< I, Ts... >
  {};

#if __cplusplus >= 201402L
  template< std::size_t I, typename T >
  using tuple_element_t = typename tuple_element< I, T >::type;
#endif

  // 20.4.2.6 Element access [tuple.elem]

  // get<I>
  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  const seq::type_by_index_t< I, Ts... >& get( const tuple< Ts... >& t ) noexcept
  {
    return static_cast< const impl::tuple_value< I, seq::type_by_index_t< I, Ts... > >& >( t.base ).get();
  }

  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  seq::type_by_index_t< I, Ts... >& get( tuple< Ts... >& t ) noexcept
  {
    return static_cast< impl::tuple_value< I, seq::type_by_index_t< I, Ts... > >& >( t.base ).get();
  }

  template< std::size_t I, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  seq::type_by_index_t< I, Ts... >&& get( tuple< Ts... >&& t ) noexcept
  {
    using type = seq::type_by_index_t< I, Ts... >;
    return static_cast< type&& >( static_cast< impl::tuple_value< I, type >& >( t.base ).get() );
  }

  // get<T> helper
  namespace impl
  {
    template< typename T, typename... Ts >
    using count_of = seq::sum< std::size_t, ( std::is_same< T, Ts >::value ? 1 : 0 )... >;

    template< typename, typename, typename... >
    struct index_of_impl;

    template< std::size_t... Is, typename T, typename... Ts >
    struct index_of_impl< seq::index_sequence< Is... >, T, Ts... >
      : seq::sum< std::size_t, ( std::is_same< T, Ts >::value ? Is : 0 )... >
    {
      static_assert( count_of< T, Ts... >::value > 0, "T not found within Ts..." );
      static_assert( count_of< T, Ts... >::value < 2, "T must be unique within Ts..." );
    };

    template< typename T, typename... Ts >
    using index_of = index_of_impl< seq::index_sequence_for< Ts... >, T, Ts... >;
  }

  // get<T>
  template< typename T, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  const T& get( const tuple< Ts... >& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( t );
  }

  template< typename T, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  T& get( tuple< Ts... >& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( t );
  }

  template< typename T, typename... Ts >
  TAOCPP_TUPLE_CONSTEXPR
  T&& get( tuple< Ts... >&& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( std::move( t ) );
  }

  // 20.4.2.7 Relational operators [tuple.rel]

  // operators helper
  namespace impl
  {
    template< typename >
    struct tuple_equal;

    template< std::size_t... Is >
    struct tuple_equal< seq::index_sequence< Is... > >
    {
      template< typename T, typename U >
      TAOCPP_TUPLE_CONSTEXPR
      bool operator()( const T& lhs, const U& rhs ) const
      {
#ifdef TAOCPP_FOLD_EXPRESSIONS
        return ( static_cast< bool >( get< Is >( lhs ) == get< Is >( rhs ) ) && ... );
#else
        bool result = true;
        using swallow = bool[];
        (void)swallow{ ( result = result && static_cast< bool >( get< Is >( lhs ) == get< Is >( rhs ) ) )..., true };
        return result;
#endif
      }
    };

    template< typename >
    struct tuple_less;

    template< std::size_t... Is >
    struct tuple_less< seq::index_sequence< Is... > >
    {
      template< typename T, typename U >
      TAOCPP_TUPLE_CONSTEXPR
      bool operator()( const T& lhs, const U& rhs ) const
      {
        bool result = false;
#ifdef TAOCPP_DUMMY // TAOCPP_FOLD_EXPRESSIONS
        // TODO: This fold expression does not work as expected. Why?
        (void)( ( ( result = static_cast< bool >( get< Is >( lhs ) < get< Is >( rhs ) ) ) || static_cast< bool >( get< Is >( rhs ) < get< Is >( lhs ) ) ) || ... );
#else
        bool no_result_yet = false;
        using swallow = bool[];
        (void)swallow{ ( no_result_yet = no_result_yet || ( result = static_cast< bool >( get< Is >( lhs ) < get< Is >( rhs ) ) ) || static_cast< bool >( get< Is >( rhs ) < get< Is >( lhs ) ) )..., true };
        (void)no_result_yet;
#endif
        return result;
      }
    };
  }

  // operators
  template< typename... Ts, typename... Us, typename = impl::enable_if_t< sizeof...( Ts ) == sizeof...( Us ) > >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator==( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return impl::tuple_equal< seq::index_sequence_for< Ts... > >()( lhs, rhs );
  }

  template< typename... Ts, typename... Us >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator!=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( lhs == rhs );
  }

  template< typename... Ts, typename... Us, typename = impl::enable_if_t< sizeof...( Ts ) == sizeof...( Us ) > >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator<( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return impl::tuple_less< seq::index_sequence_for< Ts... > >()( lhs, rhs );
  }

  template< typename... Ts, typename... Us >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator>=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( lhs < rhs );
  }

  template< typename... Ts, typename... Us >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator>( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return rhs < lhs;
  }

  template< typename... Ts, typename... Us >
  TAOCPP_TUPLE_CONSTEXPR
  bool operator<=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( rhs < lhs );
  }

  // 20.4.2.8 Tuple traits [tuple.traits]

  // TODO: Specialize uses_allocator is supported by the standard library

  // 20.4.2.9 Tuple specialized algorithms [tuple.special]

  // TODO: Should this be moved to std::? Or have "using std::swap;" somewhere?

  // swap
  template< typename... Ts >
  void swap( tuple< Ts... >& lhs, tuple< Ts... >& rhs )
    noexcept( noexcept( lhs.swap( rhs ) ) )
  {
    lhs.swap( rhs );
  }

  // (continued:) 20.4.2.4 Tuple creation functions [tuple.creation]

  // tuple_cat helper
  namespace impl
  {
    template< std::size_t M, std::size_t... Ns >
    struct count_less_or_equal
      : seq::sum< std::size_t, ( ( Ns <= M ) ? 1 : 0 )... >
    {};

    template< typename, typename >
    struct expand;

    template< std::size_t... Is, std::size_t... Ns >
    struct expand< seq::index_sequence< Is... >, seq::index_sequence< Ns... > >
    {
      using type = seq::index_sequence< count_less_or_equal< Is, Ns... >::value... >;
    };

    template< typename I, typename S >
    using expand_t = typename expand< I, S >::type;

    template< typename... >
    struct tuple_cat_result;

    template< std::size_t... Os, std::size_t... Is, typename... Ts >
    struct tuple_cat_result< seq::index_sequence< Os... >, seq::index_sequence< Is... >, Ts... >
    {
      using type = tuple< typename tuple_element< Is, seq::type_by_index_t< Os, Ts... > >::type... >;
    };

    template< typename... Ts >
    using tuple_cat_result_t = typename tuple_cat_result< Ts... >::type;

    template< typename... Ts >
    struct tuple_cat_helper
    {
      using tuple_size_sequence = seq::index_sequence< tuple_size< Ts >::value... >;
      using result_index_sequence = seq::make_index_sequence< seq::sum< tuple_size_sequence >::value >;

      using outer_index_sequence = expand_t< result_index_sequence, seq::inclusive_scan_t< tuple_size_sequence > >;
      using inner_index_sequence = seq::minus_t< result_index_sequence, seq::map_t< outer_index_sequence, seq::exclusive_scan_t< tuple_size_sequence > > >;

      using result_type = tuple_cat_result_t< outer_index_sequence, inner_index_sequence, Ts... >;
    };

    template< typename R, std::size_t... Os, std::size_t... Is, typename T >
    TAOCPP_TUPLE_CONSTEXPR
    R tuple_cat( seq::index_sequence< Os... >, seq::index_sequence< Is... >, T t )
    {
      return R( get< Is >( get< Os >( t ) )... );
    }
  }

  // tuple_cat
  template< typename... Ts, typename H = impl::tuple_cat_helper< typename std::remove_reference< Ts >::type... >, typename R = typename H::result_type >
  TAOCPP_TUPLE_CONSTEXPR
  R tuple_cat( Ts&&... ts )
  {
    return impl::tuple_cat< R >( typename H::outer_index_sequence(), typename H::inner_index_sequence(), forward_as_tuple( std::forward< Ts >( ts )... ) );
  }
}

#undef TAOCPP_TUPLE_CONSTEXPR

#endif // TAOCPP_INCLUDE_TUPLE_HPP
