#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;

	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	map<int, queue<int>> m;
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
