#include <iostream>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  rep(i, n - 1) loop(j, i + 1, n) {
    if ((a[i] - a[j]) % (n - 1)) continue;
    cout << a[i] << ' ' << a[j] << endl;
    return 0;
  }
}
