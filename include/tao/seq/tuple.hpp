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

namespace tao
{
  namespace impl
  {
    // TODO: This is a tuple reference implementation, it is known to be incomplete!

    // TODO: Add proper noexcept()-specifications everywhere
    // TODO: Respect C++11/C++14 differences (e.g., constexpr)

    template< typename T >
    using is_nothrow_swappable = std::integral_constant< bool, noexcept( swap( std::declval< T& >(), std::declval< T& >() ) ) >;

    template< std::size_t I, typename T >
    struct tuple_value
    {
      T value;

      tuple_value() {} // TODO: Check for reference-types
      explicit tuple_value( const T& v ) : value( v ) {}
      explicit tuple_value( T&& v ) : value( std::move( v ) ) {}

      bool swap( tuple_value& v ) noexcept( is_nothrow_swappable< T >::value )
      {
        using std::swap;
        swap( value, v.value );
        return true;
      }
    };

    template< typename, typename... >
    struct tuple_base;

    template< std::size_t... Is, typename... Ts >
    struct tuple_base< seq::index_sequence< Is... >, Ts... >
      : tuple_value< Is, Ts >...
    {
      tuple_base() = default;
      tuple_base( const tuple_base& ) = default;
      tuple_base( tuple_base&& ) = default;

      tuple_base& operator=( const tuple_base& ) = default;
      tuple_base& operator=( tuple_base&& ) = default;

      // TODO: Add more ctors

      // TODO: Add assignment

      template< typename... Us, typename = typename std::enable_if< sizeof...( Us ) == sizeof...( Is ) >::type >
      explicit tuple_base( Us&&... us )
        : tuple_value< Is, Ts >( std::forward< Us >( us ) )...
      {}

      void swap( tuple_base& v ) noexcept( seq::is_all< impl::is_nothrow_swappable< Ts >::value... >::value )
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

  // tuple
  template< typename... Ts >
  struct tuple
    : impl::tuple_base< seq::index_sequence_for< Ts... >, Ts... >
  {
  private:
    using base = impl::tuple_base< seq::index_sequence_for< Ts... >, Ts... >;

  public:
    using base::base;

    void swap( tuple& v ) noexcept( noexcept( base::swap( v ) ) )
    {
      base::swap( v );
    }
  };

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

  template< std::size_t I, typename T >
  using tuple_element_t = typename tuple_element< I, T >::type;

  // get<I>
  template< std::size_t I, typename... Ts >
  constexpr const seq::type_by_index_t< I, Ts... >& get( const tuple< Ts... >& t ) noexcept
  {
    return static_cast< const impl::tuple_value< I, seq::type_by_index_t< I, Ts... > >& >( t ).value;
  }

  template< std::size_t I, typename... Ts >
  constexpr seq::type_by_index_t< I, Ts... >& get( tuple< Ts... >& t ) noexcept
  {
    return static_cast< impl::tuple_value< I, seq::type_by_index_t< I, Ts... > >& >( t ).value;
  }

  template< std::size_t I, typename... Ts >
  constexpr seq::type_by_index_t< I, Ts... >&& get( tuple< Ts... >&& t ) noexcept
  {
    using type = seq::type_by_index_t< I, Ts... >;
    return static_cast< type&& >( static_cast< impl::tuple_value< I, type >& >( t ).value );
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
      static_assert( count_of< T, Ts... >::value > 0, "error: T not found within Ts..." );
      static_assert( count_of< T, Ts... >::value < 2, "error: T must be unique within Ts..." );
    };

    template< typename T, typename... Ts >
    using index_of = index_of_impl< seq::index_sequence_for< Ts... >, T, Ts... >;

    struct ignore_t
    {
      template< typename U >
      ignore_t& operator=( U&& )
      {
        return *this;
      }
    };
  }

  // get<T>
  template< typename T, typename... Ts >
  constexpr const T& get( const tuple< Ts... >& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( t );
  }

  template< typename T, typename... Ts >
  constexpr T& get( tuple< Ts... >& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( t );
  }

  template< typename T, typename... Ts >
  constexpr T&& get( tuple< Ts... >&& t ) noexcept
  {
    return get< impl::index_of< T, Ts... >::value >( std::move( t ) );
  }

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
  R make_tuple( Ts&&... ts )
  {
    return R( std::forward< Ts >( ts )... );
  }

  // forward_as_tuple
  template< typename... Ts >
  tuple< Ts&&... > forward_as_tuple( Ts&&... ts ) noexcept
  {
    return tuple< Ts&&... >( std::forward< Ts >( ts )... );
  }

  // tie
  template< typename... Ts >
  tuple< Ts&... > tie( Ts&... ts ) noexcept
  {
    return tuple< Ts&... >( ts... );
  }

  // ignore
  namespace
  {
    impl::ignore_t ignore;
  }

  // operators helper
  namespace impl
  {
    template< typename >
    struct tuple_equal;

    template< std::size_t... Is >
    struct tuple_equal< seq::index_sequence< Is... > >
    {
#ifdef TAOCPP_FOLD_EXPRESSIONS
      template< typename T, typename U >
      constexpr bool operator()( const T& lhs, const U& rhs ) const
      {
        return ( static_cast< bool >( get< Is >( lhs ) == get< Is >( rhs ) ) && ... );
      }
#else
      template< typename... Ts, typename... Us >
      bool operator()( const tuple< Ts... >& lhs, const tuple< Us... >& rhs ) const
      {
        bool result = true;
        using swallow = bool[];
        (void)swallow{ ( result = result && static_cast< bool >( get< Is >( lhs ) == get< Is >( rhs ) ) )..., true };
        return result;
      }
#endif
    };

    template< typename >
    struct tuple_less;

    template< std::size_t... Is >
    struct tuple_less< seq::index_sequence< Is... > >
    {
#ifdef TAOCPP_FOLD_EXPRESSIONS
      template< typename T, typename U >
      constexpr bool operator()( const T& lhs, const U& rhs ) const
      {
        bool result = false;
        ( ( ( result = static_cast< bool >( get< Is >( lhs ) < get< Is >( rhs ) ) ) || ( !static_cast< bool >( get< Is >( rhs ) < get< Is >( lhs ) ) ) ) && ... );
        return result;
      }
#else
      template< typename... Ts, typename... Us >
      bool operator()( const tuple< Ts... >& lhs, const tuple< Us... >& rhs ) const
      {
        bool result = false;
        bool no_result = true;
        using swallow = bool[];
        (void)swallow{ ( no_result = no_result && ( ( result = static_cast< bool >( get< Is >( lhs ) < get< Is >( rhs ) ) ) || ( !static_cast< bool >( get< Is >( rhs ) < get< Is >( lhs ) ) ) ) )... };
        return result;
      }
#endif
    };
  }

  // operators
  template< typename... Ts, typename... Us >
  constexpr bool operator==( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return impl::tuple_equal< seq::index_sequence_for< Ts... > >()( lhs, rhs );
  }

  template< typename... Ts, typename... Us >
  constexpr bool operator!=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( lhs == rhs );
  }

  template< typename... Ts, typename... Us >
  constexpr bool operator<( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return impl::tuple_less< seq::index_sequence_for< Ts... > >()( lhs, rhs );
  }

  template< typename... Ts, typename... Us >
  constexpr bool operator>=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( lhs < rhs );
  }

  template< typename... Ts, typename... Us >
  constexpr bool operator>( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return rhs < lhs;
  }

  template< typename... Ts, typename... Us >
  constexpr bool operator<=( const tuple< Ts... >& lhs, const tuple< Us... >& rhs )
  {
    return !( rhs < lhs );
  }

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
      using type = tuple< tuple_element_t< Is, seq::type_by_index_t< Os, Ts... > >... >;
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
    R tuple_cat( seq::index_sequence< Os... >, seq::index_sequence< Is... >, T t )
    {
      return R( get< Is >( get< Os >( t ) )... );
    }
  }

  // tuple_cat
  template< typename... Ts, typename H = impl::tuple_cat_helper< typename std::remove_reference< Ts >::type... >, typename R = typename H::result_type >
  R tuple_cat( Ts&&... ts )
  {
    return impl::tuple_cat< R >( typename H::outer_index_sequence(), typename H::inner_index_sequence(), forward_as_tuple( std::forward< Ts >( ts )... ) );
  }

  // swap
  template< typename... Ts >
  void swap( tuple< Ts... >& lhs, tuple< Ts... >& rhs ) noexcept( noexcept( lhs.swap( rhs ) ) )
  {
    lhs.swap( rhs );
  }
}

#endif // TAOCPP_INCLUDE_TUPLE_HPP
