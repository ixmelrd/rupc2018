#include <algorithm>
#include <iostream>
#include <map>
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

  LazySegTree(const int n, const T &x) {
    while (size < n) size *= 2;
    tree.assign(size * 2, x);
    lazy.assign(size * 2, actionM.id());
  }

  template<typename InputIterator> LazySegTree(InputIterator first, InputIterator last) {
    int n = std::distance(first, last);
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

template<typename T = bool> struct andMonoid {
  using value_type = T;
  constexpr value_type id() { return true; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return a & b; }
};

template<typename T> struct updateMonoid {
  using value_type = pair<bool, T>;
  constexpr value_type id() { return {false, T()}; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return b.first ? b : a; }
};

template<typename T> struct RAndQ_RUQ_Trait {
  using FoldMonoid = andMonoid<T>;
  using ActionMonoid = updateMonoid<T>;
  typename FoldMonoid::value_type apply(typename FoldMonoid::value_type t, typename ActionMonoid::value_type q) { return q.first ? q.second : t; }
};

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  multimap<int, int> w;
  vector<int> d(m + q), a(m + q), b(m + q);
  rep(i, m + q) cin >> d[i] >> a[i] >> b[i];
  rep(i, m + q) w.emplace(d[i] << 1 | (i < m), i);
  vector<int> ans(q);
  LazySegTree<RAndQ_RUQ_Trait<bool>> lst(2 * n, false);
  for (auto &p : w) {
    int i = p.second;
    if (i < m) {
      lst.act(2 * a[i] - 1, 2 * b[i], {true, true});
    } else {
      ans[i - m] = b[i] <= a[i] || lst.fold(2 * a[i] - 1, 2 * b[i]);
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
