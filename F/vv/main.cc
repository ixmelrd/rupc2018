#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
#define all(v) (v).begin(), (v).end()
using namespace std;

template<typename Monoid> constexpr typename Monoid::value_type powm(typename Monoid::value_type a, int b) {
  Monoid m;
  typename Monoid::value_type c = m.id();
  while (b) {
    if (b & 1) c = m(c, a);
    b >>= 1;
    a = m(a, a);
  }
  return c;
}

template<typename LSTTrait> class LazySegTree {
  using FoldMonoid = typename LSTTrait::FoldMonoid;
  using ActionMonoid = typename LSTTrait::ActionMonoid;
  using T = typename FoldMonoid::value_type;
  using Q = typename ActionMonoid::value_type;

  LSTTrait lstTrait; // apply :: (T, Q) -> T
  FoldMonoid foldM;
  ActionMonoid actionM;
  int size = 1;
  std::vector<T> tree; // 1-indexed
  std::vector<Q> lazy; // 1-indexed

  void flush(int i, int l, int r) {
    tree[i] = lstTrait.apply(tree[i], powm<ActionMonoid>(lazy[i], r - l));
    if (i < size) {
      lazy[i * 2] = actionM(lazy[i * 2], lazy[i]);
      lazy[i * 2 + 1] = actionM(lazy[i * 2 + 1], lazy[i]);
    }
    lazy[i] = actionM.id();
  }

public:
  LazySegTree(const int n = 0) {
    while (size < n) size *= 2;
    tree.assign(size * 2, foldM.id());
    lazy.assign(size * 2, actionM.id());
  }

  template<typename InputIterator> LazySegTree(InputIterator first, InputIterator last) {
    size_t n = std::distance(first, last);
    while (size < n) size *= 2;
    tree.resize(size * 2, foldM.id());
    lazy.resize(size * 2, actionM.id());
    std::copy(first, last, tree.begin() + size);
    for (int i = size - 1; i >= 1; i--) tree[i] = foldM(tree[i * 2], tree[i * 2 + 1]);
  }

  // [l, r)
  void act(int l, int r, const Q x) { act(l, r, x, 1, 0, size); }
  void act(const int l, const int r, const Q x, int i, int a, int b) {
    flush(i, a, b);
    if (b <= l || r <= a) return;
    if (l <= a && b <= r) {
      lazy[i] = actionM(lazy[i], x);
      flush(i, a, b);
      return;
    }
    act(l, r, x, i * 2, a, (a + b) / 2);
    act(l, r, x, i * 2 + 1, (a + b) / 2, b);
    tree[i] = foldM(tree[i * 2], tree[i * 2 + 1]);
  }

  // [l, r)
  T fold(int l, int r) { return fold(l, r, 1, 0, size); }
  T fold(int l, int r, int i, int a, int b) {
    flush(i, a, b);
    if (b <= l || r <= a) return foldM.id();
    if (l <= a && b <= r) return tree[i];
    T lhs = fold(l, r, i * 2, a, (a + b) / 2);
    T rhs = fold(l, r, i * 2 + 1, (a + b) / 2, b);
    tree[i] = foldM(tree[i * 2], tree[i * 2 + 1]);
    return foldM(lhs, rhs);
  }
};

template<typename T, T upperInf = std::numeric_limits<T>::max()> struct minMonoid {
  using value_type = T;
  constexpr value_type id() { return upperInf; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return a < b ? a : b; }
};

template<typename T> struct updateMonoid {
  using value_type = pair<bool, T>;
  constexpr value_type id() { return {false, T()}; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return b.first ? b : a; }
};

template<typename T, T upperInf = std::numeric_limits<T>::max()> struct RMQ_RUQ_Trait {
  using FoldMonoid = minMonoid<T, upperInf>;
  using ActionMonoid = updateMonoid<T>;
  typename FoldMonoid::value_type apply(typename FoldMonoid::value_type t, typename ActionMonoid::value_type q) { return q.first ? q.second : t; }
};

class RangeUnionFind {
  LazySegTree<RMQ_RUQ_Trait<int>> lst;

public:
  RangeUnionFind(const int n) {
    vector<int> ufInit(n);
    iota(ufInit.begin(), ufInit.end(), 0);
    lst = LazySegTree<RMQ_RUQ_Trait<int>>(ufInit.begin(), ufInit.end());
  }

  int root(int x) {
    int a = lst.fold(x, x + 1);
    if (a == x) return x;
    int b = root(a);
    lst.act(x, x + 1, {true, b});
    return b;
  }

  bool same(const int a, const int b) { return root(a) == root(b); }

  void unite(int a, int b) { // unite [a, b)
    int r = root(a);
    if (a == b) return;
    lst.act(a, b, {true, r});
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
  RangeUnionFind ruf(n);
  for (auto &p : v) {
    if (p.type == 0) {
      ruf.unite(p.a, p.b + 1);
    } else {
      ans[p.id] = p.b <= p.a || ruf.same(p.a, p.b);
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
