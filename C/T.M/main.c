#include<stdio.h>
int R[2],C[2],H[2][200010],N[2][200010];
//評価関数（いまはMAX）
int hyouka(int a,int b,int i){
  if(C[i]<b)return 1;
  if(C[i]<a||b==0)return 0;
  return N[i][H[i][a]]<N[i][H[i][b]]?1:0;
}
//挿入関数
void hin(int a,int j){
  int i=C[j]++;
  for(N[j][H[j][0]=R[j]]=a;hyouka(0,i/2,j);i/=2)H[j][i]=H[j][i/2];
  H[j][i]=R[j]++;
}
//取り出す関数
int hout(int l){
  int rt=H[l][1],i,j=2,k=H[l][--C[l]];
  for(i=1;hyouka(i,C[l],l);i=j)H[l][i]=H[l][j=i*2+1-hyouka(i*2,i*2+1,l)];
  H[l][j/2]=k;
  return rt;
}
int main(){
  int n,d[100010],f=0,i;
  R[0]=R[1]=C[0]=C[1]=1;
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%d",&d[i]);
  for(i=0;i<n;i++){
    hin(d[  i  ],0);
    hin(d[n-i-1],1);
    //printf("!%d %d\n",N[0][H[0][1]],N[1][H[1][1]]);
    while(C[0]-1&&N[0][H[0][1]]==N[1][H[1][1]]){
      hout(0);
      hout(1);
    }
    if(C[0]==1){
      if(f)printf(" ");
      printf("%d",i+1);
      f=1;
    }
    //printf("%d %d\n",C[0],i);
  }
  printf("\n");
  return 0;
}
