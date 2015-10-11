# The Art of C++ / Sequences

[![License](https://img.shields.io/github/license/taocpp/sequences.svg)](#license)
[![TravisCI](https://travis-ci.org/taocpp/sequences.svg)](https://travis-ci.org/taocpp/sequences)
[![Issues](https://img.shields.io/github/issues/taocpp/sequences.svg)](https://github.com/taocpp/sequences/issues)

The Art of C++ / Sequences is a zero-dependency C++11 header-only library that provides efficient algorithms to generate and work on [`std::integer_sequence`](http://en.cppreference.com/w/cpp/utility/integer_sequence).

# Compatibility

* The library support C++11 or newer version.
* On C++11, it provides `tao::seq::integer_sequence` itself.
* From C++14 on it uses `std::integer_sequence`.
* It is tested with GCC 4.7+ and Clang 3.4+.

# Provided algorithms and examples

* Header `tao/seq/make_integer_sequence.hpp`

  Efficient versions of sequence generators.

  * `make_integer_sequence< typename T, T N >`
  * `make_index_sequence< std::size_t N >`
  * `index_sequence_for< typename... Ts >`

* Header `tao/seq/sum.hpp`

  Integral constant to provide the sum of `Ns`.

  * `sum< typename T, T... Ns >`
  * `sum< typename S >`

* Header `tao/seq/partial_sum.hpp`

  Integral constant to provide the sum of the first `I` elements of `Ns`.

  * `partial_sum< std::size_t I, typename T, T... Ns >`
  * `partial_sum< std::size_t I, typename S >`

* Header `tao/seq/exclusive_scan.hpp`

  Provides a sequence with the exclusive scan of the input sequence.

  * `exclusive_scan_t< typename T, T... Ns >`
  * `exclusive_scan_t< typename S >`

* Header `tao/seq/inclusive_scan.hpp`

  Provides a sequence with the inclusive scan of the input sequence.

  * `inclusive_scan_t< typename T, T... Ns >`
  * `inclusive_scan_t< typename S >`

* Header `tao/seq/plus.hpp`

  Provides a sequence which is the element-wise sum of its input sequences.

  * `plus_t< typename SR, typename SL >`

* Header `tao/seq/minus.hpp`

  Provides a sequence which is the element-wise sum of its input sequences.

  * `minus_t< typename SR, typename SL >`

# Efficiency

All algorithms have a constant instantiation depth and are implemented in a non-recursive way. The only exception is `make_integer_sequence.hpp`, where the instantiation depth is O(log N).

# More documentation will come soon...
