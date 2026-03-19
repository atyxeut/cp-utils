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

#include <always.hpp>

struct union_find {
  // if f[i] >= 0: f[i] is the set that i is in
  // if f[i] < 0: i is the root of its set, and abs(f[i]) is the size of it
  I8_<int> f;

  union_find(int n) : f(n, -1) {}

  int find(int x) {
    return f[x] < 0 ? x : f[x] = find(f[x]);
  }

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

  int size(int x) {
    return -f[find(x)];
  }

  bool connected(int x, int y) {
    return find(x) == find(y);
  }
};
