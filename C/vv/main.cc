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
    int size = 1;
    while (size < n) size *= 2;
    vector<int> v(size * 2);
    rep(i, n) {
      {
        int j = b[i] + size;
        v[j]++;
        while (j /= 2) v[j] = v[j * 2] | v[j * 2 + 1];
      }
      {
        int j = b[n - 1 - i] + size;
        v[j]--;
        while (j /= 2) v[j] = v[j * 2] | v[j * 2 + 1];
      }
      {
        int acc = 0;
        for (int l = size, r = size * 2; l < r; l /= 2, r /= 2) {
          if (l & 1) acc |= v[l++];
          if (r & 1) acc |= v[--r];
        }
        if (acc == 0) ans.emplace_back(i + 1);
      }
    }
  }
  int m = static_cast<int>(ans.size());
  rep(i, m) cout << ans[i] << " \n"[i == m - 1];
}
