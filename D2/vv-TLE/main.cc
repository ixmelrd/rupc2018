#include <iostream>
#include <queue>
#include <tuple>
#define int long long
#define loop(i, a, n) for (i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
constexpr int INF = 1000000000000000000;
constexpr int perm[3][2] = {{0, 1}, {1, 2}, {2, 0}};
constexpr int pow3[12] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147};
using namespace std;

using Graph = vector<vector<pair<int, int>>>;
using state = pair<int, int>;

int n, m, s, t;
int e[100000][4];
int i, j;
Graph g;
priority_queue<state, vector<state>, greater<state>> q;
vector<int> dist;
int d, v;
int mini = INF;

signed main() {
  scanf("%lld %lld %lld %lld", &n, &m, &s, &t);
  rep(i, m) rep(j, 4) scanf("%lld", &e[i][j]);
  if (m > 11) {
    for (;;) {}
  }
  --s, --t;
  rep(i, pow3[m]) {
    g = Graph(n);
    rep(j, m) {
      int p = i / pow3[j] % 3;
      g[e[j][perm[p][0]] - 1].emplace_back(e[j][perm[p][1]] - 1, e[j][3]);
      g[e[j][perm[p][1]] - 1].emplace_back(e[j][perm[p][0]] - 1, e[j][3]);
    }
    q = priority_queue<state, vector<state>, greater<state>>();
    dist = vector<int>(n, INF);
    dist[s] = 0;
    q.emplace(0, s);
    while (q.size()) {
      tie(d, v) = q.top();
      q.pop();
      if (dist[v] < d) continue;
      for (auto &p : g[v]) {
        if (dist[p.first] > dist[v] + p.second) {
          dist[p.first] = dist[v] + p.second;
          q.emplace(dist[p.first], p.first);
        }
      }
    }
    if (mini > dist[t]) mini = dist[t];
  }
  printf("%lld\n", mini);
}
