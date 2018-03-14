#include <iostream>
#include <vector>
#include <numeric>
#include <functional>
#include <algorithm>
#include <tuple>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX_N = 100000;

class rangeUpdateQuery {
	protected:
		function<int(int, int)> op;
		int identity;

		int n, dat[4 * MAX_N];
		int dat_lazy[4 * MAX_N];
		int query(int a, int b, int k, int l, int r){
			evaluate(k);

			if(b <= l || r <= a) return identity;
			else if(a <= l && r <= b) return dat[k];
			else{
				int vl = query(a, b, k * 2, l, (l + r) / 2);
				int vr = query(a, b, k * 2 + 1, (l + r) / 2, r);
				return op(vl, vr);
			}
		}
		inline void evaluate(int k){
			if(dat_lazy[k] == identity) return;
			dat[k] = dat_lazy[k];
			if(k < n){
				dat_lazy[2 * k] = dat_lazy[k];
				dat_lazy[2 * k + 1] = dat_lazy[k];
			}
			dat_lazy[k] = identity;
		}
		void update(int a, int b, int k, int l, int r, int x){
			evaluate(k);

			if(r <= a || b <= l) return;

			if(a <= l && r <= b){
				dat_lazy[k] = op(dat_lazy[k], x);
			}else if(l < b && a < r){
				evaluate(k);
				update(a, b, k * 2, l, (l + r) / 2, x);
				update(a, b, k * 2 + 1, (l + r) / 2, r, x);
			}
		}
	public:
		rangeUpdateQuery(vector<int> a, int e, function<int(int, int)> f){
			op = f;
			identity = e;

			int n_ = a.size();
			n = 1;
			while(n <= n_) n *= 2;
			for(int i = 0; i < n * n; i++){
				dat_lazy[i] = identity;
			}
			for(int i = n; i < n * n; i++){
				dat[i] = a[i - n];
			}
			for(int i = n - 1; i >= 1; i--){
				dat[i] = min(dat[i * 2], dat[i * 2 + 1]);
			}
		}
		int query(int a, int b){
			return query(a,b,1,0,n);
		}
		void update(int s, int t, int x){
			update(s, t, 1, 0, n, x);
		}
		int get(int a){ return query(a, a + 1); };
};

struct Query {
	int id, d, s, t;
	bool ans;
};

struct Edge {
	int d, a, b;
};

int main() {
	int N, M ,Q;
	cin >> N >> M >> Q;

	vector<Edge> e(M);
	for (int i = 0; i < M; i++) {
		auto& p = e[i];
		cin >> p.d >> p.a >> p.b;
	}

	vector<Query> q(Q);
	for (int i = 0; i < Q; i++) {
		auto& p = q[i];
		p.id = i;
		cin >> p.d >> p.s >> p.t;
	}

	sort(e.begin(), e.end(), [](const Edge& l, const Edge& r){ return l.d < r.d; });
	sort(q.begin(), q.end(), [](const Query& l, const Query& r){ return l.d < r.d; });

	vector<int> a(N);
	iota(a.begin(), a.end(), 1);

	rangeUpdateQuery maxi(a, -INT_MAX, [](const int& a, const int& b){ return max(a, b); });
	rangeUpdateQuery mini(a,  INT_MAX, [](const int& a, const int& b){ return min(a, b); });

	auto it = e.begin();
	for (int i = 0; i < Q; i++) {
		while (it != e.end() and (*it).d <= q[i].d) {
			auto p = *it;

			// segTree は 1-index
			int left = mini.get(p.a - 1);
			int right = maxi.get(p.b - 1);

			int maximum = max(p.b, maxi.get(p.b - 1));
			int minimum = min(p.a, mini.get(p.a - 1));

			maxi.update(left - 1, right, maximum);
			mini.update(left - 1, right, minimum);
			it++;
		}

		//for (int i = 0; i < N; i++) { if(i) cout << ' '; cout << maxi.get(i); } cout << endl;
		//for (int i = 0; i < N; i++) { if(i) cout << ' '; cout << mini.get(i); } cout << endl;

		auto& p = q[i];
		p.ans = maxi.get(p.s - 1) >= p.t ? true : false;
	}

	sort(q.begin(), q.end(), [](const Query& l, const Query& r){ return l.id < r.id; });

	for (auto i : q) {
		cout << (i.ans ? "Yes" : "No") << endl;
	}
}
