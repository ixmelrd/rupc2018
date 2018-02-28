#include <iostream>
#include <vector>
#include <set>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  set<int> b;
  for (int &x : a) cin >> x;
  rep(i, n) {
    int x;
    cin >> x;
    b.insert(x);
  }
  if (b.size() == n) {
    cout << "Yes" << endl;
    return 0;
  }
  vector<int> c(n, a[0]), d(n);
  rep(i, n) d[i] = b.count(a[i]) ? a[0] : a[1];
  cout << "No" << endl;
  rep(i, n) cout << c[i] << " \n"[i == n - 1];
  rep(i, n) cout << d[i] << " \n"[i == n - 1];
}
