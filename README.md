# The Art of C++ / Sequences

[![License](https://img.shields.io/github/license/taocpp/sequences.svg)](#license)
[![TravisCI](https://travis-ci.org/taocpp/sequences.svg)](https://travis-ci.org/taocpp/sequences)
[![Issues](https://img.shields.io/github/issues/taocpp/sequences.svg)](https://github.com/taocpp/sequences/issues)

The Art of C++ / Sequences is a zero-dependency C++11 header-only library that provides efficient algorithms to generate and work on [`std::integer_sequence`](http://en.cppreference.com/w/cpp/utility/integer_sequence).

# Compatibility

* The library support C++11 or newer.
* It is tested with GCC 4.7+ and Clang 3.4+.
* It provides `tao::seq::integer_sequence`.
* When available, the above is a type-alias to `std::integer_sequence`.

# Provided algorithms and examples

* Header `tao/seq/make_integer_sequence.hpp`

  Efficient versions of sequence generators.

  * `make_integer_sequence< typename T, T N >`
  * `make_index_sequence< std::size_t N >`
  * `index_sequence_for< typename... Ts >`

  Examples:

  * `make_integer_sequence<int,0>` ➙ `integer_sequence<int>`
  * `make_integer_sequence<int,1>` ➙ `integer_sequence<int,0>`
  * `make_integer_sequence<int,3>` ➙ `integer_sequence<int,0,1,2>`
  * `make_index_sequence<0>` ➙ `index_sequence<>`
  * `make_index_sequence<1>` ➙ `index_sequence<1>`
  * `make_index_sequence<5>` ➙ `index_sequence<0,1,2,3,4>`
  * `index_sequence_for<int,void,long>` ➙ `index_sequence<0,1,2>`

  Notes:

  The implementation has O(log N) instantiation depth. This allows for very large sequences without the need to increase the compiler's default instantiation depth limits. For example, GCC and Clang generate `index_sequence<10000>` in ~0.15s (on my machine, of course). The standard library version, when trying to create `index_sequence<5000>` and with its O(N) implementation, requires ~30s, >3GB of RAM and `-ftemplate-depth=5100`.

* Header `tao/seq/sum.hpp`

  Integral constant to provide the sum of `Ns`.

  * `sum< typename T, T... Ns >`
  * `sum< typename S >`

  Examples:

  * `sum<int,1,4,3,1>::value` ➙ `9`
  * `sum<make_index_sequence<5>>::value` ➙ `10`

* Header `tao/seq/partial_sum.hpp`

  Integral constant to provide the sum of the first `I` elements of `Ns`.

  * `partial_sum< std::size_t I, typename T, T... Ns >`
  * `partial_sum< std::size_t I, typename S >`

  Examples:

  * `partial_sum<0,int,1,4,3,1>::value` ➙ `0`
  * `partial_sum<2,int,1,4,3,1>::value` ➙ `5`
  * `partial_sum<4,make_index_sequence<5>>::value` ➙ `6`

* Header `tao/seq/exclusive_scan.hpp`

  Provides a sequence with the exclusive scan of the input sequence.

  * `exclusive_scan_t< typename T, T... Ns >`
  * `exclusive_scan_t< typename S >`

  Examples:

  * `exclusive_scan_t<int,1,4,0,3,1>` ➙ `integer_sequence<int,0,1,5,5,8>`

* Header `tao/seq/inclusive_scan.hpp`

  Provides a sequence with the inclusive scan of the input sequence.

  * `inclusive_scan_t< typename T, T... Ns >`
  * `inclusive_scan_t< typename S >`

  Examples:

  * `inclusive_scan_t<int,1,4,0,3,1>` ➙ `integer_sequence<int,1,5,5,8,9>`

* Header `tao/seq/plus.hpp`

  Provides a sequence which is the element-wise sum of its input sequences.

  * `plus_t< typename L, typename R >`

  Examples:

  * `using A = index_sequence<1,4,0,3,1>`
  * `using B = make_index_sequence<5>`
  * `plus_t<A,B>` ➙ `index_sequence<1,5,2,6,5>`

* Header `tao/seq/minus.hpp`

  Provides a sequence which is the element-wise sum of its input sequences.

  * `minus_t< typename L, typename R >`

  Examples:

  * `using A = integer_sequence<int,1,4,0,3,1>`
  * `using B = integer_sequence<int,0,1,2,3,4>`
  * `minus_t<A,B>` ➙ `integer_sequence<int,1,3,-2,0,-3>`
  * `minus_t<B,A>` ➙ `integer_sequence<int,-1,-3,2,0,3>`

* Header `tao/seq/head.hpp`

  Integral constant to provide the first element of a non-empty sequence.

  * `head< typename T, T... >`
  * `head< typename S >`

* Header `tao/seq/tail.hpp`

  Removed the first element of a non-empty sequence.

  * `tail_t< typename T, T... >`
  * `tail_t< typename S >`


* Header `tao/seq/select.hpp`

  Integral constant to provide the `I`th element of a non-empty sequence.

  * `select< std::size_t I, typename T, T... >`
  * `select< std::size_t I, typename S >`

* Header `tao/seq/map.hpp`

  Map a sequence of indices to a sequence of values.

  * `map_t< typename I, typename M >`

  Examples:

  * `using I = index_sequence<1,0,3,2,1,1,3>`
  * `using M = integer_sequence<int,5,6,-7,8,9>`
  * `map_t<I,M>` ➙ `integer_sequence<int,6,5,8,-7,6,6,8>`

# More documentation will come soon...
