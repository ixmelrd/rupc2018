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
  cout << a[0] << ' ' << a[0] << endl;
}
