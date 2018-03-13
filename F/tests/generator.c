#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
int a[200010],b[200010],t[200010];
void swap(int *a,int *b){
  int t=*a;
  *a=*b;
  *b=t;
}
void out(int n,int m,int q,char *s){
  int i;
  FILE *f;
  f=fopen(s,"w");
  fprintf(f,"%d %d %d\n",n,m,q);
  for(i=0;i<q;i++){
    if(rnd.next(0,1))swap(&a[i+m],&b[i+m]);
  }
  for(i=0;i<m+q;i++)fprintf(f,"%d %d %d\n",t[i],a[i],b[i]);
  fclose(f);
}
void MakeABT(int n,int m){
  int i;
  for(i=0;i<m;i++){
    a[i]=rnd.next(MIN_A ,n-1);
    b[i]=rnd.next(a[i]+1,n  );
    t[i]=rnd.next(MIN_D,MAX_D);
  }
}
void challenge00(){
  int n=MAX_N,m=n-1,q=MAX_Q,i;
  char s[100]={"60_challenge_00.in"};
  for(i=0;i<m;i++){
    a[i]=1;
    b[i]=i+2;
    t[i]=i+1;
  }
  for(i=0;i<q;i++){
    a[i+m]=rnd.next(MIN_S,n);
    b[i+m]=rnd.next(MIN_T,n);
    t[i+m]=rnd.next(MIN_D,n);
  }
  out(n,m,q,s);
}
void challenge01(){
  int n=MAX_N,m=n/2,q=MAX_Q,i;
  char s[100]={"60_challenge_01.in"};
  for(i=0;i<m;i++){
    a[i]=i*2;
    b[i]=i*2+1;
    t[i]=rnd.next(MIN_D,MAX_D);
  }
  for(i=0;i<q;i++){
    a[i+m]=rnd.next(MIN_S,n);
    b[i+m]=rnd.next(MIN_T,n);
    t[i+m]=rnd.next(MIN_D,MAX_D);
  }
  out(n,m,q,s);
}
int main() {
  int n,m,q,i,j;
  char s[100];
  rnd.setSeed(time(0)+getpid());

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,10);
    m=rnd.next(MIN_M,8);
    q=rnd.next(MIN_Q,8);
    sprintf(s,"50_random_small_%02d.in",i);
    MakeABT(n,m+q);
    for(j=0;j<m+q;j++)t[j]=t[j]%20+MIN_A;
    out(n,m,q,s);
  }

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    m=rnd.next(MIN_M,MAX_M);
    q=rnd.next(MIN_Q,MAX_Q);
    sprintf(s,"51_random_large_%02d.in",i);
    MakeABT(n,m+q);
    out(n,m,q,s);
  }

  n=MIN_N;
  m=MIN_M;
  q=MIN_Q;
  sprintf(s,"52_MIN_00.in");
  MakeABT(n,m+q);
  out(n,m,q,s);

  for(i=0;i<10;i++){
    n=MAX_N;
    m=MAX_M;
    q=MAX_Q;
    sprintf(s,"53_MAX_%02d.in",i);
    MakeABT(n,m+q);
    out(n,m,q,s);
  }

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,50);
    m=rnd.next(MIN_M,MAX_M);
    q=rnd.next(MIN_Q,MAX_Q);
    sprintf(s,"54_Nsmall_%02d.in",i);
    MakeABT(n,m+q);
    out(n,m,q,s);
  }
  
  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    m=rnd.next(MIN_M,50);
    q=rnd.next(MIN_Q,MAX_Q);
    sprintf(s,"55_Msmall_%02d.in",i);
    MakeABT(n,m+q);
    out(n,m,q,s);
  }

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    m=rnd.next(MIN_M,MAX_M);
    q=rnd.next(MIN_Q,MAX_Q);
    sprintf(s,"56_DEsmall_%02d.in",i);
    MakeABT(n,m+q);
    for(j=0;j<m+q;j++)t[j]=(t[j]%100)+MIN_D;
    out(n,m,q,s);
  }

  challenge00();
  //challenge01();

  
  return 0;
}
