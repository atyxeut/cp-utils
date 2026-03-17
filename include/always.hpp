// Copyright (C) 2026 atyxeut
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

using namespace std;

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;
using i128 = __int128;
using u128 = unsigned __int128;

using f32 = float;
using f64 = double;
using f80 = long double;
using f128 = __float128;

// I*_, J*_, K*_, L*_, M*_, N*_, O*_, P*_: identifiers that are only used internally
// already used:
// I0_ ~ I9_
// Ia_

template <bool B, class T = void>
using I0_ = typename enable_if<B, T>::type;

template <class T>
using I7_ = numeric_limits<T>;

template <class T>
using I8_ = vector<T>;

using Ia_ = size_t;

template <class T, Ia_ N>
using I9_ = array<T, N>;

template <class T, Ia_... D>
struct I2_;

template <class T, Ia_ D>
struct I2_<T, D> {
  using t = I9_<T, D>;
};

template <class T, Ia_ D, Ia_... d>
struct I2_<T, D, d...> : I2_<typename I2_<T, d...>::t, D> {};

template <class T, Ia_... D>
using mdarr = typename I2_<T, D...>::t;

template <class T, Ia_ C>
struct I3_ : I3_<typename I3_<T, C - 1>::t, 1> {};

template <class T>
struct I3_<T, 1> {
  using t = I8_<T>;
};

template <class T, Ia_ C>
using mdvec = typename I3_<T, C>::t;

using I4_ = false_type;
using I5_ = true_type;

template <class T>
struct I6_ : I4_ {};

template <class T, Ia_ N>
struct I6_<I9_<T, N>> : I5_ {};

template <class E, Ia_ D, class T>
I0_<!I6_<E>::value> fill_arr(I9_<E, D>& a, const T& v) {
  a.fill(v);
}

template <class E, Ia_ D, class T>
I0_<I6_<E>::value> fill_arr(I9_<E, D>& a, const T& v) {
  for (auto& i : a)
    fill_arr(i, v);
}

template <class E, class D, class T>
I8_<E> make_vec(D s, const T& v) {
  return I8_<E>(s, v);
}

template <class E, class D, class... T, Ia_ N = sizeof...(T)>
I0_<N, mdvec<E, N>> make_vec(D s, T&&... a) {
  return I8_<mdvec<E, N - 1>>(s, make_vec<E>(forward<T>(a)...));
}
