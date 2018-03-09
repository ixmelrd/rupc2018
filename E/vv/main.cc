#include <iostream>
#include <vector>
#define int long long
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
constexpr int MOD = 1000000000 + 7;
using namespace std;

template<int mod> struct modint {
  int v;
  modint(int a = 0) : v(((a % mod) + mod) % mod) {}
  modint operator+(const modint<mod> &b) const { return (v + b.v) % mod; }
  friend modint<mod> &operator+=(modint<mod> &a, const modint<mod> &b) { return a = a + b; }
  friend ostream &operator<<(ostream &os, const modint<mod> &a) { return os << a.v; }
};

istream &operator>>(istream &is, vector<int> &v) {
  string s;
  is >> s;
  v.reserve(s.size());
  for (char c : s) v.emplace_back(c - '0');
  return is;
}

template<typename T>
using v = vector<T>;

template<typename T>
void resize(vector<T> &v, const int head) { v.resize(head); }

template<typename T, typename ... X>
void resize(vector<T> &v, const int head, const X &... tail) {
  v.resize(head);
  for (auto &x: v) resize(x, tail...);
}

signed main() {
  vector<int> s;
  cin >> s;
  int n = static_cast<int>(s.size());

  v<v<v<v<modint<MOD>>>>> dp;
  resize(dp, n + 1, 2, 5, 2);
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
