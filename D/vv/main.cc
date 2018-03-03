#include <iomanip>
#include <iostream>
#include <vector>
#define int long long
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
template<typename A, typename B> void cmax(A &a, const B &b) {
  if (a < b) a = b;
}
constexpr double INF = 1e9;
using namespace std;

template<typename CommutativeGroup> class RangeFold {
  using T = typename CommutativeGroup::value_type;

  CommutativeGroup g;

  std::vector<T> cache;

public:
  RangeFold(const std::vector<T> &raw) : cache(raw) {
    size_t w = cache.size();
    loop(i, 1, w) cache[i] += cache[i - 1];
  }

  T fold(const int l, const int r) { // [l, r)
    T acc = g.id();
    if (r > 0) acc = g(acc, cache[r - 1]);
    if (l > 0) acc = g(acc, g.inv(cache[l - 1]));
    return acc;
  }
};

template<typename T> struct sumGroup {
  using value_type = T;
  constexpr value_type id() { return 0; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return a + b; }
  constexpr value_type inv(const value_type &x) { return -x; }
};

signed main() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  RangeFold<sumGroup<int>> rf(a);
  vector<vector<double>> dp(n + 1, vector<double>(n + 1, -INF));
  dp[0][0] = 0;
  loop(i, 1, 1 + n) loop(j, 1, 1 + i) loop(k, 1, 1 + i) cmax(dp[i][j], dp[i - k][j - 1] + 1.0 * rf.fold(i - k, i) / k);
  cout << fixed << setprecision(32) << dp[n][m] << endl;
}
