// SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <core.hpp>

// W is an integral
template <class W>
struct weighted_union_find {
  // if f[i] >= 0: f[i] is the set that i is in
  // if f[i] < 0: i is the root of its set, and abs(f[i]) is the size of it
  I8_<int> f;

  // w[i]: weight of i
  I8_<W> w;

  static constexpr W null = I7_<W>::max();

  weighted_union_find(int n, W t = 0) : f(n, -1), w(n, t) {}

  int find(int x) {
    if (f[x] >= 0) {
      int u = f[x];
      f[x] = find(u);
      w[x] += w[u];
      return f[x];
    }
    return x;
  }

  void unite(int x, int y, W t) {
    int u = x, v = y;
    x = find(x);
    y = find(y);
    if (x != y) {
      t += w[v] - w[u];
      if (f[x] < f[y]) {
        swap(x, y);
        t = -t;
      }
      f[y] += f[x];
      f[x] = y;
      w[x] = t;
    }
  }

  int size(int x) { return -f[find(x)]; }

  bool connected(int x, int y) { return find(x) == find(y); }

  W query(int x, int y) { return connected(x, y) ? w[x] - w[y] : null; }
};
