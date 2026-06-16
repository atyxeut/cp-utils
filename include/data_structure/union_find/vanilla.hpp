// SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <core.hpp>

struct union_find {
  // if f[i] >= 0: f[i] is the set that i is in
  // if f[i] < 0: i is the root of its set, and abs(f[i]) is the size of it
  I8_<int> f;

  union_find(int n) : f(n, -1) {}

  int find(int x) { return f[x] < 0 ? x : f[x] = find(f[x]); }

  void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
      // let x always represent the smaller set
      if (f[x] < f[y])
        swap(x, y);
      f[y] += f[x];
      f[x] = y;
    }
  }

  int size(int x) { return -f[find(x)]; }

  bool connected(int x, int y) { return find(x) == find(y); }
};
