#include<stdio.h>
int ta[100010],to[100010],co[100010],nt[100010],r=0;
long long R=1,C=1,H[2000010],N[2000010],CO[100010],id[200010],f[100010];
//評価関数（いまはMIN）
int hyouka(int a,int b){
  if(C<b)return 1;
  if(C<a||b==0)return 0;
  return N[H[a]]<N[H[b]]?1:0;
}
//挿入関数
void hin(long long a){
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
void add(int a,int b,int c){
  nt[r]=ta[a];
  to[r]=b;
  co[ta[a]=r++]=c;
}
int main(){
  int n,m,s,t,i,j,k,mi;
  scanf("%d %d %d %d",&n,&m,&s,&t);
  for(i=0;i<=n;i++)ta[i]=-1;
  while(m--){
    scanf("%d %d %d %d",&i,&j,&k,&mi);
    add(i,j,mi);
    add(i,k,mi);
    add(j,i,mi);
    add(j,k,mi);
    add(k,i,mi);
    add(k,j,mi);
  }
  for(i=1;i<=n;i++)CO[i]=1e18;
  CO[mi=s]=0;
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[mi];i+1;i=nt[i]){
      if(CO[to[i]]>CO[mi]+co[i])hin(CO[id[R]=to[i]]=CO[mi]+co[i]);
    }
    while(f[mi]&&C-1)mi=id[hout()];
  }
  printf("%lld\n",CO[t]);
  return 0;
}
