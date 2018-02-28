#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  vector<int> b(a);
  {
    int k = 0;
    map<int, int> m;
    sort(b.begin(), b.end());
    rep(i, n) if (!m.count(b[i])) m[b[i]] = k++;
    rep(i, n) b[i] = m[a[i]];
  }
  vector<int> ans;
  ans.reserve(n);
  {
    int c = 0;
    vector<int> v(n);
    rep(i, n) {
      v[b[i]]++;
      c += v[b[i]] == 1 ? 1 : v[b[i]] == 0 ? -1 : 0;
      v[b[n - 1 - i]]--;
      c += v[b[n - 1 - i]] == -1 ? 1 : v[b[n - 1 - i]] == 0 ? -1 : 0;
      if (c == 0) ans.emplace_back(i + 1);
    }
  }
  int m = static_cast<int>(ans.size());
  rep(i, m) cout << ans[i] << " \n"[i == m - 1];
}
