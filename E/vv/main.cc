#include <iostream>
#include <vector>
#define int long long
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

istream &operator>>(istream &is, vector<int> &v) {
  string s;
  is >> s;
  v.reserve(s.size());
  for (char c : s) v.emplace_back(c - '0');
  return is;
}

template <typename Head, typename Value> auto vectors(const Head &head, const Value &v) { return vector<Value>(head, v); }
template <typename Head, typename... Tail> auto vectors(Head x, Tail... tail) {
  auto inner = vectors(tail...);
  return vector<decltype(inner)>(x, inner);
}

signed main() {
  vector<int> s;
  cin >> s;
  int n = static_cast<int>(s.size());

  auto dp = vectors(n + 1, 2, 5, 2, 0LL);
  dp[0][0][0][0] = 1;

  auto f = [](int k, int l, int m) -> int {
    if ( k == 4                ) return 4;
    if ( k == 3       && m == 3) return 4;
    if ( k == 2                ) return 3;
    if ((k == 1 || l) && m == 1) return 2;
    if (                 m == 5) return 1;
    return 0;
  };

  rep(i, n) rep(j, 2) rep(k, 5) rep(l, 2) rep(m, (j ? 9 : s[i]) + 1) {
    dp[i + 1][j || m < s[i]][f(k, l, m)][k == 2 && m == 5] += dp[i][j][k][l];
  }

  cout << dp[n][0][4][0] + dp[n][1][4][0] << endl;
}
