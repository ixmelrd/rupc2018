#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

vector<int> compress(vector<int> v) {
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	return v;
}

int lb(vector<int>& v, int num){
	return lower_bound(v.begin(), v.end(), num) - v.begin();
}

int main() {
	int n;
	cin >> n;

	vector<int> in(n);
	for (int i = 0; i < n; i++) {
		cin >> in[i];
	}
	vector<int> com = compress(in);

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		a[i] = lb(com, in[i]); 
	}

	vector<queue<int>> m(n);
	for (int i = n - 1; i >= 0; i--) {
		m[a[i]].push(n - 1 - i);
	}

	int k = 0;
	vector<int> ans;
	for (int i = 0; i < n; i++) {
		auto& p = m[a[i]];

		k = max(k, p.front());
		if(i == k) ans.emplace_back(k + 1);

		p.pop();
	}

	for (int i = 0; i < ans.size(); i++) {
		if (i) cout << ' ';
		cout << ans[i];
	}
	cout << endl;
}
