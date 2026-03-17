#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <random>
#include <ratio>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#if __cplusplus >= 201703L
#include <any>
#include <charconv>
#include <string_view>
#include <variant>
#endif // C++17

#if __cplusplus >= 202002L
#include <bit>
#include <compare>
#include <numbers>
#include <ranges>
#include <span>
#include <version>
#endif // C++20

#if __cpp_lib_format >= 202311L
#include <format>
#endif

#if __cpp_lib_print >= 202406L
#include <print>
#endif

#if __cpp_lib_mdspan >= 202406L
#include <mdspan>
#endif

#if __cpp_lib_constexpr_flat_map >= 202502L
#include <flat_map>
#endif

#if __cpp_lib_constexpr_flat_set >= 202502L
#include <flat_set>
#endif

using namespace std;

#if __cplusplus >= 201402L
using string_literals::operator ""s;
#endif // C++14

#if __cplusplus >= 201703L
using string_view_literals::operator ""sv;
#endif // C++17

#if IS_LOCAL_DEBUGGING
ifstream is("test/data/debug.in");
#else
auto& is = cin;
#endif // IS_LOCAL_DEBUGGING

#if IS_DEBUG_MODE
template <class... T>
void logerr(T... _) {
#if __cplusplus >= 201703L
  ((cerr << _), ...);
#else
  int t[] {(cerr << _, 0)...};
#endif // C++17
}
#endif // IS_DEBUG_MODE

void solve();

#include <always.hpp>
#include <customize.hpp>

/** other custom header **/

/** other custom header **/

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#if IS_ONE_INPUT_MULTIPLE_TESTS
  int t;
  is >> t;
  while (t--)
    solve();
#else
  solve();
#endif // IS_ONE_INPUT_MULTIPLE_TESTS
}

void solve() {
  
}
