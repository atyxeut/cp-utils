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

#include <algorithm>

#include <always.hpp>

template <class F>
class trie {
  mdvec<int, 2> t;
  I8_<int> p, e;

  int s = 0;

  F m;

  template <int T>
  int I(Ib_& S) {
    int i = 0;
    for (char c : S) {
      int j = t[i][m(c)];
      if (!j)
        return 0;
      i = j;
    }
    return T ? p[i] : e[i];
  }

public:
  trie(int M, int C) : t(M, I8_<int>(C)), p(M), e(M) {}

  void insert(Ib_& S) {
    ++p[0];
    int i = 0;
    for (char c : S) {
      int& j = t[i][m(c)];
      if (!j)
        j = ++s;
      i = j;
      ++p[i];
    }
    ++e[i];
  }

  int count(Ib_& S) {
    return I<0>(S);
  }

  int count_has_prefix(Ib_& S) {
    return I<1>(S);
  }

  void erase(Ib_& S) {
    if (count(S)) {
      --p[0];
      int i = 0;
      for (char c : S) {
        int& j = t[i][m(c)];
        if (!--p[j]) {
          j = 0;
          return;
        }
        i = j;
      }
      --e[i];
    }
  }
};
