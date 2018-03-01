#include <algorithm>
#include <iostream>
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

struct query {
  int id, type, d, a, b;
  query(const int id, const int type, const int d, const int a, const int b) : id(id), type(type), d(d), a(a), b(b) {}
};

bool operator<(const query &a, const query &b) { return a.d < b.d; }

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<query> v;
  v.reserve(m + q);
  rep(i, m) {
    int d, a, b;
    cin >> d >> a >> b;
    v.emplace_back(0, 0, d, --a, --b);
  }
  rep(i, q) {
    int e, s, t;
    cin >> e >> s >> t;
    v.emplace_back(i, 1, e, --s, --t);
  }
  sort(v.begin(), v.end());
  vector<int> ans(q);
  UFTree uf(n);
  for (auto &p : v) {
    if (p.type == 0) {
      loop(i, p.a, p.b) uf.unite(i, i + 1);
    } else {
      ans[p.id] = p.b <= p.a || uf.same(p.a, p.b);
    }
  }
  for(auto &x: ans) cout << (x ? "YES" : "NO") << endl;
}
