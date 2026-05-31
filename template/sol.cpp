#include <bits/stdc++.h>
using namespace std;

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

#include <core.hpp>
#include <customization.hpp>

/** other custom headers **/

/** other custom headers **/

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
#if IS_ONE_INPUT_MULTIPLE_TESTS
  int _;
  is >> _;
  while (_--)
    solve();
#else
  solve();
#endif // IS_ONE_INPUT_MULTIPLE_TESTS
}

void solve() {
  
}
