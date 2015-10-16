# The Art of C++ / Sequences

[![Release](https://img.shields.io/github/release/taocpp/sequences.svg)](https://github.com/taocpp/sequences/releases/latest)
[![License](https://img.shields.io/github/license/taocpp/sequences.svg)](#license)
[![TravisCI](https://travis-ci.org/taocpp/sequences.svg)](https://travis-ci.org/taocpp/sequences)
[![Issues](https://img.shields.io/github/issues/taocpp/sequences.svg)](https://github.com/taocpp/sequences/issues)

The Art of C++ / Sequences is a zero-dependency C++11 header-only library that provides efficient algorithms to generate and work on [`std::integer_sequence`](http://en.cppreference.com/w/cpp/utility/integer_sequence).

## Compatibility

* Requires C++11 or newer.
* Tested with GCC 4.8+ and Clang 3.4+.

## Provided algorithms and examples

* All provided templates are in the nested namespace `tao::seq`.
* All templates don't use C++14 features, therefore being compatible with C++11. Sometimes, C++14/C++17 features are used conditionally, taking advantage of newer language features when available but providing C++11-compatible implementations otherwise.
* All templates use `tao::seq::integer_sequence`, etc. internally, therefore being compatible with C++11.
* All templates use `tao::seq::make_integer_sequence`, etc. internally, therefore using the most scalable solution available.

#### Header `tao/seq/integer_sequence.hpp`

Provides:

* `integer_sequence< typename T, T N >`
* `index_sequence< std::size_t N >`

Notes:

* When available (C++14 or newer), the above are type-aliases for `std::integer_sequence` and `std::index_sequence`.

#### Header `tao/seq/make_integer_sequence.hpp`

Efficient versions of sequence generators.

* `make_integer_sequence< typename T, T N >`
* `make_index_sequence< std::size_t N >`
* `index_sequence_for< typename... Ts >`

Examples:

* `make_integer_sequence<int,0>` ➙ `integer_sequence<int>`
* `make_integer_sequence<int,1>` ➙ `integer_sequence<int,0>`
* `make_integer_sequence<int,3>` ➙ `integer_sequence<int,0,1,2>`
* `make_index_sequence<0>` ➙ `index_sequence<>`
* `make_index_sequence<1>` ➙ `index_sequence<0>`
* `make_index_sequence<5>` ➙ `index_sequence<0,1,2,3,4>`
* `index_sequence_for<int,void,long>` ➙ `index_sequence<0,1,2>`

Notes:

libc++ already has very efficient versions for the above, so they are pulled in with a using-declaration. Only if we don't know if the STL's versions are at least O(log N) we provide our own implementations.

Our own implementation has O(log N) instantiation depth. This allows for very large sequences without the need to increase the compiler's default instantiation depth limits. For example, GCC and Clang generate `index_sequence<10000>` in ~0.15s (on my machine, of course). The standard library version from libstdc++, when trying to create `index_sequence<5000>` and with its O(N) implementation, requires ~30s, >3GB of RAM and `-ftemplate-depth=5100`.

#### Header `tao/seq/sum.hpp`

Integral constant to provide the sum of `Ns`.

* `sum< typename T, T... Ns >`
* `sum< typename S >`

Examples:

* `sum<int,1,4,3,1>::value` ➙ `9`
* `sum<make_index_sequence<5>>::value` ➙ `10`

#### Header `tao/seq/partial_sum.hpp`

Integral constant to provide the sum of the first `I` elements of `Ns`.

* `partial_sum< std::size_t I, typename T, T... Ns >`
* `partial_sum< std::size_t I, typename S >`

Examples:

* `partial_sum<0,int,1,4,3,1>::value` ➙ `0`
* `partial_sum<2,int,1,4,3,1>::value` ➙ `5`
* `partial_sum<4,make_index_sequence<5>>::value` ➙ `6`

#### Header `tao/seq/exclusive_scan.hpp`

Provides a sequence with the exclusive scan of the input sequence.

* `exclusive_scan_t< typename T, T... Ns >`
* `exclusive_scan_t< typename S >`

Examples:

* `exclusive_scan_t<int,1,4,0,3,1>` ➙ `integer_sequence<int,0,1,5,5,8>`

#### Header `tao/seq/inclusive_scan.hpp`

Provides a sequence with the inclusive scan of the input sequence.

* `inclusive_scan_t< typename T, T... Ns >`
* `inclusive_scan_t< typename S >`

Examples:

* `inclusive_scan_t<int,1,4,0,3,1>` ➙ `integer_sequence<int,1,5,5,8,9>`

#### Header `tao/seq/zip.hpp`

Applies a binary operation to elements from two sequences.

* `zip_t< template< typename U, U, U > class OP, typename L, typename R >`

Notes:

Both sequences may have a different element type, the resulting sequence's type is calculated with `std::common_type_t`.

#### Header `tao/seq/plus.hpp`

Provides a sequence which is the element-wise sum of its input sequences.

* `plus_t< typename L, typename R >`

Notes:

Both sequences may have a different element type, the resulting sequence's type is calculated with `std::common_type_t`.

Examples:

* `using A = index_sequence<1,4,0,3,1>`
* `using B = make_index_sequence<5>`
* `plus_t<A,B>` ➙ `index_sequence<1,5,2,6,5>`

#### Header `tao/seq/minus.hpp`

Provides a sequence which is the element-wise sum of its input sequences.

* `minus_t< typename L, typename R >`

Notes:

Both sequences may have a different element type, the resulting sequence's type is calculated with `std::common_type_t`.

Examples:

* `using A = integer_sequence<int,1,4,0,3,1>`
* `using B = integer_sequence<int,0,1,2,3,4>`
* `minus_t<A,B>` ➙ `integer_sequence<int,1,3,-2,0,-3>`
* `minus_t<B,A>` ➙ `integer_sequence<int,-1,-3,2,0,3>`

#### Header `tao/seq/head.hpp`

Integral constant to provide the first element of a non-empty sequence.

* `head< typename T, T... >`
* `head< typename S >`

#### Header `tao/seq/tail.hpp`

Removed the first element of a non-empty sequence.

* `tail_t< typename T, T... >`
* `tail_t< typename S >`

#### Header `tao/seq/select.hpp`

Integral constant to provide the `I`th element of a non-empty sequence.

* `select< std::size_t I, typename T, T... >`
* `select< std::size_t I, typename S >`

#### Header `tao/seq/concatenate.hpp`

Concatenate the values.

* `concatenate_t< typename T, typename U >`

Notes:

Both sequences may have a different element type, the resulting sequence's type is calculated with `std::common_type_t`.

#### Header `tao/seq/fold.hpp`

Integral constant calculated by "folding" a sequence of values with a given binary operation.

* `fold< template< typename U, U, U > class OP, typename T, T... >`
* `fold< template< typename U, U, U > class OP, typename S >`

#### Header `tao/seq/min.hpp`

Integral constant to provide the minimum value.

* `min< typename T, T... >`
* `min< typename S >`

Notes:

Implemented with `fold` like this:

    namespace impl
    {
      template< typename T, T A, T B >
      using min = std::integral_constant< T, ( ( A < B ) ? A : B ) >;
    }

    template< typename T, T... Ns >
    using min = fold< impl::min, T, Ns... >;

#### Header `tao/seq/max.hpp`

Integral constant to provide the maximum value.

* `max< typename T, T... >`
* `max< typename S >`

#### Header `tao/seq/map.hpp`

Map a sequence of indices to a sequence of values.

* `map_t< typename I, typename M >`

Examples:

* `using I = index_sequence<1,0,3,2,1,1,3>`
* `using M = integer_sequence<int,5,6,-7,8,9>`
* `map_t<I,M>` ➙ `integer_sequence<int,6,5,8,-7,6,6,8>`

#### Header `tao/seq/is_all.hpp`

Integral constant which is true if all boolean parameters are true (logical and).

* `is_all< bool... >`

Examples:

* `is_all<true,true,true,true>::value` ➙ `true`
* `is_all<true,true,false,true>::value` ➙ `false`
* `is_all<>::value` ➙ `true`

#### Header `tao/seq/is_any.hpp`

Integral constant which is true if any boolean parameter is true (logical or).

* `is_any< bool... >`

Examples:

* `is_any<false,true,false,false>::value` ➙ `true`
* `is_any<false,false,false,false>::value` ➙ `false`
* `is_any<>::value` ➙ `false`

## License

<a href="http://www.opensource.org/"><img height="100" align="right" src="http://wiki.opensource.org/bin/download/OSI+Operations/Marketing+%26+Promotional+Collateral/OSI_certified_logo_vector.svg"></a>

The Art of C++ is certified [Open Source](http://www.opensource.org/docs/definition.html) software. It may be used for any purpose, including commercial purposes, at absolutely no cost. It is distributed under the terms of the [MIT license](http://www.opensource.org/licenses/mit-license.html) reproduced here.

> Copyright (c) 2015 Daniel Frey
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This site and software is not affiliated with or endorsed by the Open Source Initiative.
