#include<stdio.h>
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
int rr[100010];
int lb(int l,int r,int n,int *d){
  int m=(l+r)/2;
  if(l==r)return rr[m];
  return n<=d[rr[m]]?lb(l,m,n,d):lb(m+1,r,n,d);
}
int main(){
  int n,a,d[2][100010],i;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    scanf("%d",&d[0][i]);
    hin(d[0][i]);
  }
  for(i=0;i<n;i++)rr[i]=hout()-1;
  for(d[1][0]=d[0][i=1];i<n;i++)d[1][i]=d[0][0];
  for(i=0;i<n;i++){
    scanf("%d",&a);
    d[1][lb(0,n,a,d[0])]=a;
  }
  for(i=0;i<n;i++){
    if(d[0][i]-d[1][i])goto END;
  }
  printf("Yes\n");
  return 0;
 END:;
  printf("No\n");
  for(a=0;a<2;a++){
    for(i=0;i<n;i++)printf("%d%c",d[a][i],n-i-1?' ':'\n');
  }
  return 0;
}
