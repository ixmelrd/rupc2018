// Rimeには誤差ジャッジの仕組みがないのでスペシャルジャッジ扱いになる
// また，AOJとRimeではスペシャルジャッジ用チェッカーの仕様が違うので
// マクロで場合分けをする
//
// 判定結果の出力
// - AOJでは何も出力せずに正常終了するとAC、何か出力して正常終了するとWA
//   (異常終了してはいけない)
// - Rimeでは正常終了するとAC、異常終了するとWA
//
// コマンドライン引数の与えられ方
// - Rimeでは
//   ./checker --infile $judgein --difffile $judgeout --outfile $userout
//   と実行される
// - AOJでは
//   ./checker $judgein $userout $judgeout > diff_log
//   と実行される
// checker   : 判定プログラム
// $judgein  : 入力ファイル
// $userout  : ユーザが提出したコードによる出力
// $judgeout : ジャッジが用意した出力
// diff_log  : checkerによる出力
// 
// これら切り替えるため、Rimeでテストするときには #define RIME する
// ソースコードに埋め込むと都合が悪いので、
// TESTSETで下のようにコンパイルされるように設定する
// g++ judge.cc -D RIME

#include "testlib.h"
#include <iostream>
#include <cassert>
#include <set>
using namespace std;

const double ABS_DELTA = 1e-6;
const double REL_DELTA = 1e-6;
const double TOL = 1e-9;


void WA(){
#ifdef RIME
    quit(_wa, "Wrong Answer");
#else // AOJ
    cout << "WA" << endl;
    exit(0);
#endif
}

void AC(){
#ifdef RIME
    quit(_ok, "Accepted");
#else // AOJ
    exit(0);
#endif
}

int main(int argc, char *argv[])
{

#ifdef RIME
    assert(argc == 7);
    int argc_mod = 4;
    char *argv_mod[4];
    argv_mod[0] = argv[0];
    for (int i = 1; i < argc; ++i) {
        string arg(argv[i]);
        if(arg == "--infile"){
            argv_mod[1] = argv[++i];
        } else if (arg == "--difffile") {
            argv_mod[3] = argv[++i];
        } else if (arg == "--outfile") {
            argv_mod[2] = argv[++i];
        }
    }
    registerTestlibCmd(argc_mod, argv_mod);
#else // AOJ
    // testlibと同じなのでそのまま渡す
    registerTestlibCmd(argc, argv);
#endif

    // 入力ファイルの読み込み 不要なので読み捨て
    // 読み捨てないとエラー
	int n = inf.readInt();
	set<int> s;
	for (int i = 0; i < n; i++) {
		if(i) inf.readSpace();
		s.emplace(inf.readInt());
	}
	inf.readEoln();
    inf.readEof();

    // 解答による出力ファイルを読み込み
    int a = ouf.readInt();
	ouf.readSpace();
	int b = ouf.readInt();
    ouf.readEoln();
    ouf.readEof();

    // 正答ファイルを読み込み
	while(!ans.seekEof()) ans.readChar();

    if(a != b and s.count(a) and s.count(b) and abs(b - a) % (n - 1) == 0){
        AC();
    }
    WA();
}
