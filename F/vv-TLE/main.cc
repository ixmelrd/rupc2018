#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

class UFTree {
  std::vector<int> tree, rank, _size;

public:
  UFTree(const int n) : tree(n), rank(n), _size(n, 1) { iota(tree.begin(), tree.end(), 0); }

  int root(const int x) { return tree[x] == x ? x : tree[x] = root(tree[x]); }

  bool same(const int a, const int b) { return root(a) == root(b); }

  bool unite(int a, int b) {
    a = root(a), b = root(b);
    if (a == b) return false;
    if (rank[a] < rank[b]) std::swap(a, b);
    tree[b] = a;
    _size[a] += _size[b];
    if (rank[a] == rank[b]) rank[a]++;
    return true;
  }
};

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  multimap<int, int> w;
  vector<int> d(m + q), a(m + q), b(m + q);
  rep(i, m + q) cin >> d[i] >> a[i] >> b[i];
  rep(i, m + q) w.emplace(d[i] << 1 | (i < m), i);
  vector<int> ans(q);
  UFTree uf(n);
  for (auto &p : w) {
    int i = p.second;
    if (i < m) {
      loop(j, a[i] - 1, b[i] - 1) uf.unite(j, j + 1);
    } else {
      ans[i - m] = b[i] <= a[i] || uf.same(a[i] - 1, b[i] - 1);
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
