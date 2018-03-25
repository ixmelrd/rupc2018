#include<iostream>
#include<string>
#define loop(i,a,b) for(int i=a;i<b;i++)
#define rep(i,a) loop(i,0,a)
using namespace std;

long long dp[10001][2][5][2];

int main(){
	string n;
	cin >> n;

	dp[0][0][0][0] = 1;
	// i番目まで見ている、その値未満であることが確定している、k文字目まで一致している、i - 1番目の数字が5である
	rep(i,n.size()) rep(j,2) rep(k,5) rep(l,2) {
		int lim = j ? 9 : n[i] - '0';

		rep(d,lim + 1){
			if(k == 4){		// ごちうさ数が含まれることが確定している
				dp[i + 1][j or d < lim][k][d == 5] += dp[i][j][k][l];
			}else if(		// ごちうさ数の遷移が行える
					(k == 0 and d == 5) or
					(k == 1 and d == 1) or
					(k == 2)			or
					(k == 3 and d == 3)
			  ){
				dp[i + 1][j or d < lim][k + 1][d == 5] += dp[i][j][k][l];
			}else if(k == 3 and d == 1 and l == 1){ // 5151...に対応する
				dp[i + 1][j or d < lim][2][d == 5] += dp[i][j][k][l];
			}else{			// ごちうさ数にならない。d == 5のときは一文字目まで一致したと判定する。
				dp[i + 1][j or d < lim][d == 5][d == 5] += dp[i][j][k][l];
			}

		}
	}

	long long ans = 0;
	rep(i,2){
		ans += dp[n.size()][0][4][i] + dp[n.size()][1][4][i];
	}

	cout << ans << endl;
}
