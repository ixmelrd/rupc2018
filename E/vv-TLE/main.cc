#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>
#define loop(i, a, n) for (i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
constexpr int INF = 1000000000;
using namespace std;

using Graph = vector<vector<pair<int, int>>>;
using state = pair<int, int>;

int n, m, s, t;
int e[2000][3];
int i, j;
int perm[6][3] = {{0, 1, 2}, {0, 2, 1}, {1, 0, 2}, {1, 2, 0}, {2, 0, 1}, {2, 1, 0}};
int pow6[8] = {1, 6, 36, 216, 1296, 7776, 46656, 279936};
Graph g;
priority_queue<state, vector<state>, greater<state>> q;
vector<int> dist;
int d, v;
int mini = INF;

int main() {
  scanf("%d %d %d %d", &n, &m, &s, &t);
  rep(i, m) rep(j, 3) scanf("%d", &e[i][j]);
  if (m > 7) {
    for (;;) {}
  }
  --s, --t;
  rep(i, pow6[m]) {
    g = Graph(n);
    rep(j, m) {
      int p = i / pow6[j] % 6;
      g[e[j][perm[p][0]] - 1].emplace_back(e[j][perm[p][1]] - 1, e[j][perm[p][2]]);
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
    mini = min(mini, dist[t]);
  }
  printf("%d\n", mini);
}
