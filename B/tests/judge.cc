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
#include<stdio.h>
#include "constraints.hpp"
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
int R=1,C=1,H[2000010],N[2000010];
//評価関数（いまはMAX）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]?1:0;
}
//挿入関数
void hin(int a){
  int i=C++;
  for(N[H[0]=R]=a;hyouka(0,i/2);i/=2)H[i]=H[i/2];
  H[i]=R++;
}
//取り出す関数
int hout(){
  int rt=H[1],i,j=2,k=H[--C];
  for(i=1;hyouka(i,C);i=j)H[i]=H[j=i*2+1-hyouka(i*2,i*2+1)];
  H[j/2]=k;
  return rt;
}
int lb(int l,int r,int n,int *d){
  int m=(l+r)/2;
  if(l==r)return m;
  return n<=d[m]?lb(l,m,n,d):lb(m+1,r,n,d);
}

int main(int argc, char *argv[]){

#ifdef RIME
  assert(argc == 7);
  int argc_mod = 4;
  char *argv_mod[4];
  argv_mod[0] = argv[0];
  for (int i = 1; i < argc; ++i) {
    string arg(argv[i]);
    if     (arg == "--infile"  )argv_mod[1] = argv[++i];
    else if(arg == "--difffile")argv_mod[3] = argv[++i];
    else if(arg == "--outfile" )argv_mod[2] = argv[++i];
  }
  registerTestlibCmd(argc_mod, argv_mod);
#else // AOJ
  // testlibと同じなのでそのまま渡す
  registerTestlibCmd(argc, argv);
#endif

  int n,a[4][100010],r[100010],i,j,ok=0;
  char outs[100010],anss[5],no[]={"No"};
  
  // 入力ファイルの読み込み 
  n=inf.readInt();
  inf.readEoln();
  for(i=0;i<2;i++){
    for(j=0;j<n;j++){
      if(j)inf.readSpace();
      a[i][j]=inf.readInt();
    }
    inf.readEoln();
  }
  inf.readEof();
  
  // 解答による出力ファイルを読み込み
  strcpy(outs,ouf.readLine().c_str());
  if(strcmp(outs,no)==0){
    for(i=2;i<4;i++){
      for(j=0;j<n;j++){
	if(j)ouf.readSpace();
	a[i][j]=ouf.readInt(MIN_a,n);
      }
      ouf.readEoln();
    }
  }
  ouf.readEof();
  
  // 正答ファイルを読み込み
  strcpy(anss,ans.readLine().c_str());
  while(!ans.seekEof())ans.readChar();
  ans.readEof();
  
  if(strcmp(anss,outs))WA();//Yes Noが違う
  if(strcmp(outs,no))AC();//Noでない->Yes AC!!
  
  /*for(i=0;i<n;i++)hin(a[0][i]);
  for(i=0;i<n;i++){
    for(j=0;j<4;j++)d[j][i]=a[j][H[1]-1];
    hout();
  }
  for(i=2;i<4;i++){
    for(j=0;j<n;j++){
      if(a[i][j]-d[0][lb(0,n,a[i][j],d[0])])WA();//存在しない
    }
  }
  //*/
  for(i=0;i<n;i++)r[a[0][i]]=i;
  for(i=0;i<n;i++){
    j=r[a[1][i]];
    if(a[2][j]!=a[3][j])WA();
    if(a[2][i]!=a[3][i])ok=1;
  }
  // AC();
  if(ok)AC();
  WA();
}
