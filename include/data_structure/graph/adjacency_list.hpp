// SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <algorithm>

#include <core.hpp>

template <class W = int>
struct out_edge {
  int v;
  W w;
};

template <class W>
using Ic_ = out_edge<W>;

template <class W>
bool operator<(const Ic_<W>& x, const Ic_<W>& y) {
  return x.v < y.v;
}

// V: the count of total vertexes
// E: the count of total edges
// W: an integral type of edge weight
template <int V, int E, class W = int>
class adjacency_list {
  // vertex number starts at 0
  // edge number starts at 1, and 0 stands for no edge

  // let the object have static storage duration, e.g. be a global variable,
  // so the members are zero-initialized

  // w[i]: weight of the i-th edge
  W w[E];

  // f[i]: first out edge number of vertex i
  // x[i]: the number of the next edge to traverse
  // g[i]: end vertex of the i-th edge
  // z[i]: count of i's neighbors
  // b: a buffer for `sort_neighbors` function
  // s: total edge count
  int f[V], x[E], g[E], z[V], b[E], s;

  using T = Ic_<W>;

  // enable range based for loop for neighbor traversal
  struct R {
    adjacency_list* p;
    int e;

    struct I {
      adjacency_list* p;
      int e;

      T operator*() const { return {p->g[e], p->w[e]}; }

      I& operator++() {
        e = p->x[e];
        return *this;
      }

      bool operator!=(const I& o) const { return e != o.e; }
    };

    I begin() const { return I{p, e}; }

    I end() const { return I{p, 0}; }
  };

public:
  void add_edge(int u, int v, W t = 1) {
    // new edge appears earlier than the original first out edge of vertex u
    x[++s] = f[u];
    f[u] = s;
    ++z[u];
    g[s] = v;
    w[s] = t;
  }

  R neighbors(int u) { return R{this, f[u]}; }

  template <class F = less<T>>
  void sort_neighbors(int u, F&& c = less<T>{}) {
    int k = 0, e = f[u];
    for (; e; e = x[e])
      b[k++] = e;
    if (k) {
      sort(b, b + k, [this, &c](int x, int y) { return c(T{g[x], w[x]}, T{g[y], w[y]}); });
      f[u] = b[0];
      for (int i = 0; i + 1 < k; ++i)
        x[b[i]] = b[i + 1];
      x[b[k - 1]] = 0;
    }
  }
};
