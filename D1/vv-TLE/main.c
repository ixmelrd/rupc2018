#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#define I(n,t) do c=getchar();while(c<'0');while('0'<=c&&c<='9'){n=n*10+(t)(c-'0');c=getchar();}
#define Z (Y<<1)
typedef uint16_t u16;typedef uint32_t u32;typedef uint64_t u64;
typedef struct{u32 t;double w;} E;typedef struct{E*e;u16 c,s;} D;typedef struct{u32 v;double d;} S;
u32 W;S H[251001];

int main() {
  u16 n=0,m=0;u64 a[501]={};u32 c;I(n,u16)I(m,u16);
  for(u16 i=1;i<=n;i++){I(a[i],u64)a[i]+=a[i-1];}
  u32 V=(u32)(n+1)*(u32)(n+1);u32 X=V;D A[251001];
  while(X--){A[X].e=(E*)malloc(sizeof(E)*10);A[X].c=10;A[X].s=0;}
  for(u16 i=1;i<=n;i++)for(u16 j=1;j<=i;j++)for(u16 k=1;k<=i;k++){
    u32 s=(i-k)*(n+1)+(j-1);
    if(A[s].s==A[s].c){A[s].c<<=1;A[s].e=(E*)realloc(A[s].e,sizeof(E)*A[s].c);}
    A[s].e[A[s].s].t=i*(n+1)+j;A[s].e[A[s].s].w=-1.0*(a[i]-a[i-k])/k;A[s].s++;
  }
  double d[251001];for(u32 i=0;i<V;i++)d[i]=1e18;d[0]=0.0;
  {u32 i;for(i=W++;i>0&&0.0<H[(i-1)>>1].d;i=(i-1)>>1)H[i]=H[(i-1)>>1];H[i].v=0;H[i].d=0.0;}
  while(W){
    u32 Y=0,j;S p=H[0],L=H[--W];
    while(Z+1<W&&L.d>H[j=(Z+1+(Z+2<W&&H[Z+1].d>H[Z+2].d))].d)H[Y]=H[j],Y=j;
    H[Y]=L;if(p.d>d[p.v])continue;
    for(u16 i=0;i<A[p.v].s;i++)if(p.d+A[p.v].e[i].w<d[A[p.v].e[i].t]){
      d[A[p.v].e[i].t]=p.d+A[p.v].e[i].w;u32 k;
      for(k=W++;k>0&&d[A[p.v].e[i].t]<H[(k-1)>>1].d;k=(k-1)>>1)H[k]=H[(k-1)>>1];
      H[k].v=A[p.v].e[i].t;H[k].d=d[A[p.v].e[i].t];
    }
  }
  printf("%.10lf\n",-d[n*(n+1)+m]);
}
