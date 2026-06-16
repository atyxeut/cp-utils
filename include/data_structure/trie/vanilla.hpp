// SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <cstring>

#include <core.hpp>

// N is the total count of nodes this trie is allowed to have
// C is the total count of distinct characters that will appear
template <int N, int C, class F>
class trie {
  // the root node is the 0-th node

  // let the object have static storage duration, e.g. be a global variable,
  // so the members are all zero-initialized

  // t[i][j]: the direct child's number of the i-th node's j-th branch
  // p[i]: strings that passed the i-th node
  // e[i]: strings that end at the i-th node
  // s: the count of total nodes, except the root node
  int t[N][C], p[N], e[N], s;

  // a hash function that maps a character to an integer
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
  void clear() {
    memset(t, 0, sizeof t);
    memset(p, 0, sizeof p);
    memset(e, 0, sizeof e);
    s = 0;
  }

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

  int count(Ib_& S) { return I<0>(S); }

  int count_has_prefix(Ib_& S) { return I<1>(S); }

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
