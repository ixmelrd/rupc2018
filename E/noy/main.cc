#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void addEdge(vector<vector<pair<int, int>>>& g, int a, int b, int c){
	//cout << a << ' ' << b << ' ' << c << endl;
	g[a].emplace_back(b,c);
	g[b].emplace_back(a,c);
}

vector<int> cost;

int bfs(vector<vector<pair<int, int>>>& g, int s, int t, int v){
	vector<vector<int>> dis(v, vector<int>(v,1e8));
	dis[s][s] = 0;
	//cout << s << ' ' << t << endl;

	queue<pair<int, int>> q;
	q.push(make_pair(s, s));

	while(not q.empty()){
		pair<int, int> tmp = q.front(); q.pop();
		int cur, last;
		tie(cur, last) = tmp;

		for(auto e : g[cur]){
			if(last / 3 == e.first / 3) continue;
			//if(pre / 3 == cur / 3 and cur / 3 == e.first / 3) continue;
			//if(pre == e.first) continue;
			if(e.second == 0){
				if(dis[e.first][last] > dis[cur][last]){
					dis[e.first][last] = dis[cur][last];
					q.push(make_pair(e.first, last));
				}
			}else{
				if(dis[e.first][cur] > dis[cur][last] + e.second){
					dis[e.first][cur] = dis[cur][last] + e.second;
					q.push(make_pair(e.first, cur));
				}
			}
		}
	}

	//for (int i = 0; i < dis.size(); i++) { cout << i << ' ' << dis[i] << endl; }

	int mini = 1e8;
	for (int i = 0; i < v; i++) {
		mini = min(mini, dis[t][i]);
	}
	return mini;
}

int main() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	
	vector<int> a(m), b(m), c(m);
	for (int i = 0; i < m; i++) {
		cin >> a[i] >> b[i] >> c[i];
		a[i]--; b[i]--; c[i]--;
	}

	vector<vector<pair<int, int>>> g(3 * m + 2);
	vector<vector<int>> tmp(n);
	for (int i = 0; i < m; i++) {
		cost.emplace_back(max({a[i], b[i], c[i]}) + 1);
		int x = i * 3;
		int y = i * 3 + 1;
		int z = i * 3 + 2;
		if(a[i] != b[i]) addEdge(g, x, y, c[i] + 1);
		addEdge(g, x, z, b[i] + 1);
		if(b[i] != c[i]) addEdge(g, y, z, a[i] + 1);

		tmp[ a[i] ].emplace_back(x);
		if(a[i] != b[i]) tmp[ b[i] ].emplace_back(y);
		if(b[i] != c[i]) tmp[ c[i] ].emplace_back(z);
	}

	for(auto v : tmp){
		for (int i = 0; i < v.size(); i++) {
			for (int j = i + 1; j < v.size(); j++) {
				addEdge(g, v[i], v[j], 0);
			}
		}
	}

	for (int i = 0; i < tmp[s - 1].size(); i++) {
		addEdge(g, 3 * m, tmp[s - 1][i], 0);
	}

	for (int i = 0; i < tmp[t - 1].size(); i++) {
		addEdge(g, 3 * m + 1, tmp[t - 1][i], 0);
	}

	cout << bfs(g, 3 * m, 3 * m + 1, 3 * m + 2) << endl;
}
