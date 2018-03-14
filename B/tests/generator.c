#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
int MIN(int a,int b){return a<b?a:b;}
void swap(int *a,int *b){
  int t=*a;
  *a=*b;
  *b=t;
}
void out(int n,int *d,int *a,int *b,char *s){
  FILE *f;
  int i,j;
  f=fopen(s,"w");
  fprintf(f,"%d\n",n);
  for(i=0;i<n;i++)fprintf(f,"%d%c",d[a[i]],n-i-1?' ':'\n');
  for(i=0;i<n;i++)fprintf(f,"%d%c",d[b[i]],n-i-1?' ':'\n');
  fclose(f);
}
void MakeNum(int n,int *d){
  int i;
  for(i=0;i<n;i++)d[i]=i+1;
}
void MakeIdx(int n,int *d){
  int i;
  for(i=0;i<n;i++)d[i]=i;
  for(i=0;i<n;i++)swap(&d[i],&d[rnd.next(0,n-1)]);
}
void MakeRnd(int n,int *d){
  int i;
  for(i=0;i<n;i++)d[i]=rnd.next(0,n-1);
}
int main(){
  int n,d[100010],a[100010],b[100010],i,j,k;
  char s[100];
  rnd.setSeed(time(0)+getpid());

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,8);
    sprintf(s,"50_random_small_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeRnd(n,b);
    out(n,d,a,b,s);
  }

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,8);
    sprintf(s,"50_random_small_Yes_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeIdx(n,b);
    out(n,d,a,b,s);
  }



  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"51_random_large_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeRnd(n,b);
    out(n,d,a,b,s);
  }
  
  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"51_random_large_Yes_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeIdx(n,b);
    out(n,d,a,b,s);
  }

  n=MIN_N;
  sprintf(s,"52_MIN_00.in");
  MakeNum(n,d);
  MakeIdx(n,a);
  MakeRnd(n,b);
  out(n,d,a,b,s);
 

  for(i=0;i<10;i++){
    n=MAX_N;
    sprintf(s,"53_MAX_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeRnd(n,b);
    out(n,d,a,b,s);
  }

  for(i=0;i<10;i++){
    n=MAX_N;
    sprintf(s,"53_MAX_Yes_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeIdx(n,b);
    out(n,d,a,b,s);
  }

  for(i=0;i<5;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"54_B_Same_A_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    out(n,d,a,a,s);
  }

  for(i=0;i<5;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"55_Gap_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    for(j=0;j<n;j++)b[(j+1)%n]=a[j];
    out(n,d,a,b,s);
  }

  for(i=0;i<5;i++){
    n=MAX_N;
    sprintf(s,"55_Gap_MAX_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    for(j=0;j<n;j++)b[(j+1)%n]=a[j];
    out(n,d,a,b,s);
  }

  for(i=0;i<5;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"56_B_Same_All_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    b[0]=rnd.next(0,n-1);
    for(j=1;j<n;j++)b[j]=b[0];
    out(n,d,a,b,s);
  }

  for(i=0;i<10;i++){
    n=rnd.next(MIN_N,MAX_N);
    sprintf(s,"57_B_Same_One_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeIdx(n,b);
    j=k=rnd.next(0,n-1);
    while(j==k)k=rnd.next(0,n-1);
    b[j]=b[k];
    out(n,d,a,b,s);
  }

  for(i=0;i<10;i++){
    n=10;
    sprintf(s,"60_challenge_%02d.in",i);
    MakeNum(n,d);
    MakeIdx(n,a);
    MakeIdx(n,b);
    for(j=0;b[j]-a[i];j++);
    k=j;
    while(j==k)k=rnd.next(0,n-1);
    b[j]=b[k];
    out(n,d,a,b,s);
  }
  return 0;
}

