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
#include <iostream>

#include <always.hpp>

using I1_ = ostream;

I1_& operator <<(I1_& o, u128 n)
{
  if (!n)
    return o << 0;

  string b;
  for (; n; n /= 10)
    b += n % 10 + '0';
  reverse(b.begin(), b.end());
  return o << b;
}

I1_& operator <<(I1_& o, i128 n)
{
  if (n == I7_<i128>::min())
    return o << '-' << u128(n);
  if (n < 0)
    return o << '-' << u128(-n);
  return o << u128(n);
}
