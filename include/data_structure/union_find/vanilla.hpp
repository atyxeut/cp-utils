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

#include <numeric>

#include <always.hpp>

using namespace std;

struct union_find
{
  I8_<int> f, s;

  union_find(int n) : f(n), s(n, 1)
  {
    iota(begin(f), end(f), 0);
  }

  int find(int x)
  {
    return x != f[x] ? f[x] = find(f[x]) : x;
  }

  void unite(int x, int y)
  {
    x = find(x);
    y = find(y);
    if (x != y) {
      if (s[x] < s[y])
        swap(x, y);
      f[y] = x;
      s[x] += s[y];
    }
  }

  bool is_connected(int x, int y)
  {
    return find(x) == find(y);
  }
};
