#include<stdio.h>
int MIN(int a,int b){return a<b?a:b;}
int ta[100010],to[100010],co[100010],nt[100010],cu[100010],r=0;
int R=1,C=1,H[2000010],N[2000010],CO[200010],id[200010],f[100010];
//評価関数（いまはMIN）
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
void add(int a,int b,int c,int n){
  nt[r]=ta[a];
  to[r]=b;
  cu[r]=r+n;
  co[ta[a]=r++]=c;
}
int main(){
  int n,m,s,t,i,j,k,ans=1e9,mi;
  scanf("%d %d %d %d",&n,&m,&s,&t);
  for(i=0;i<=m*6;i++)ta[i]=-1;
  for(i=0;i<m;i++){
    scanf("%d %d %d",&i,&j,&k);
    add(i,j,k, 3);
    add(i,k,j, 4);
    add(j,i,k,-1);
    add(j,k,i, 1);
    add(k,i,j,-4);
    add(k,j,i,-3);
  }
  //for(i=0;i<n;i++)printf("%d ",ta[i+1]);printf("\n");
  //for(i=0;i<r;i++)printf("%d %d %d %d %d\n",i,to[i],nt[i],co[i],cu[i]);
  for(i=0;i<r;i++)CO[i]=1e9;
  /*for(i=0;i<n;i++){
    printf(":%d\n",i+1);
    for(j=ta[i+1];j+1;j=nt[j])printf("%d ",to[j]);
    printf("\n");
    }//*/
  for(i=ta[s];i+1;i=nt[i])hin(CO[id[R]=i]=co[i]);
  mi=id[hout()];
  //for(i=1;i<R;i++)printf("%d ",id[i]);printf("\n");
  //printf("%d\n",mi);
  while(f[mi]-1){
    f[mi]=1;
    for(i=ta[to[mi]];i+1;i=nt[i]){
      if(i==cu[mi])continue;
      if(CO[to[i]]>CO[mi]+co[i])hin(CO[id[R]=to[i]]=CO[mi]+co[i]);
    }
    while(f[mi]-1&&CO[i])mi=id[hout()];
  }
  for(i=0;i<r;i++){//printf("%d ",CO[i]);
    if(to[i]-t)continue;
    ans=MIN(ans,CO[i]);
  }//printf("\n");
  printf("%d\n",ans);
  return 0;
}
