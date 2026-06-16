// SPDX-FileCopyrightText: 2026 atyxeut <atyxeut@outlook.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <algorithm>
#include <iostream>

#include <core.hpp>

using I1_ = ostream;

I1_& operator <<(I1_& o, u128 n) {
  if (!n)
    return o << 0;

  Ib_ b;
  for (; n; n /= 10)
    b += n % 10 + '0';
  reverse(b.begin(), b.end());
  return o << b;
}

I1_& operator <<(I1_& o, i128 n) {
  if (n == I7_<i128>::min())
    return o << '-' << u128(n);
  if (n < 0)
    return o << '-' << u128(-n);
  return o << u128(n);
}
