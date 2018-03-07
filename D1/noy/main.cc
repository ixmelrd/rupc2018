#include <iostream>
#include <vector>
#include <iomanip>
#include <cassert>
using namespace std;

// [l, r) の区間の平均を返す
double getAverage(vector<double>& sum, double l, double r){
	return (sum[r] - sum[l]) / (r - l);
}

int main() {
	int n, m;
	cin >> n >> m;

	vector<double> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}

	if (n == 1) {
		cout << fixed << setprecision(5) << a[0] << endl;
		return 0;
	}

	vector<double> sum(n + 1, 0);
	for (int i = 0; i < n; i++) {
		sum[i + 1] = sum[i] + a[i];
	}

	// dp[i][j] := 区間[0, i]を j 回圧縮したときの数列の総和の最大値
	vector<vector<double>> dp(n + 1, vector<double>(n + 1,-1e9));
	dp[0][0] = 0;
	for (int i = 1; i <= n; i++) {					// i-index
		for (int com = 1; com <= i; com++) {		// 圧縮回数
			for (int len = 1; len <= i; len++) {	// 圧縮する区間の長さ
				dp[i][com] = max(dp[i][com], dp[i - len][com - 1] + getAverage(sum, i - len, i));
			}
		}
	}

	cout << fixed << setprecision(5) << dp[n][m] << endl;
}
