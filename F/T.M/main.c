#include<stdio.h>
int MAX(int a,int b){return a<b?b:a;}
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
int T,E[2][400010]={};
void init(int n){
  int i;
  for(T=1;T<n;T*=2);
  for(i=0;i<T;i++)E[0][i+T]=E[1][i+T]=i;
  for(i=0;i<T;i++)E[0][i  ]=E[1][i  ]=-1;
}
void set(int a,int b,int n,int m,int l,int r,int i){//セグ木m,[a,b)をnにする
  //printf("%d %d %d %d %d %d %d\n",a,b,n,m,l,r,i);
  if(b<=l||r<=a)return;
  if(a<=l&&r<=b)E[m][i]=n;
  else{
    set(a,b,n,m,l,(l+r)/2,i*2  );
    set(a,b,n,m,(l+r)/2,r,i*2+1);
  }
}
int get(int n,int m){
  int a=E[m][n+T];
  for(n+=T;n;n/=2)a=E[m][n]+1?E[m][n]:a;
  return a;
}
int main(){
  int n,m,q,a,b,c,s[100010],t[100010],d[100010],i;
  for(i=0;i<100010;i++)E[0][i]=E[1][i]=-1;
  scanf("%d %d %d",&n,&m,&q);n++;
  init(n);/*
  for(i=0;i<n;i++){
    printf("%d %d\n",get(i,0,0,n,1),get(i,1,0,n,1));
  }printf("\n");return 0;//*/ 
  for(i=0;i<m+q;i++){
    scanf("%d %d %d",&a,&s[i],&t[i]);
    hin(a);
  }
  for(i=0;i<m+q;i++){
    /*for(a=b=1;a<2*T;a++){
      if(a==b){
	printf("\n");
	b*=2;
      }
      printf("%2d ",E[0][a]);
      }
      printf("\n\n");
    for(a=1;a<n;a++)printf("%d %d\n",get(a,0),get(a,1));
    printf("\n");//*/
    a=hout()-1;//printf("%d %d %d\n",a,s[a],t[a]);
    if(a<m){
      b=get(s[a],0);
      c=get(t[a],1);//printf("!%d %d\n",b,c);
      set(b,c+1,b,0,0,T,1);//printf("\n");
      set(b,c+1,c,1,0,T,1);//printf("endset\n");
    }
    else{
      b=get(s[a],1);
      //c=get(t[a],1);//printf("?%d %d\n",b,c);
      d[a-m]=t[a]>b?0:1;
    }
  }
  for(i=0;i<q;i++)printf("%s\n",d[i]?"Yes":"No");
  return 0;
}
