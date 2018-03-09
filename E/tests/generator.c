#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
void out(char *d,char *s){
  int i;
  FILE *f;
  f=fopen(s,"w");
  fprintf(f,"%s\n",d);
  fclose(f);
}
void MakeNum(int n,char *d){
  d[n]=0;
  while(--n)d[n]=rnd.next(0,9)+'0';
  d[0]=rnd.next(1,9)+'0';
}
int main() {
  int i,n;
  char d[10010],s[100],g[5]={"5103"};

  for(i=0;i<10;i++){
    n=rnd.next(MIN_digits_of_N,10);
    sprintf(s,"50_random_small_%02d.in",i);
    MakeNum(n,d);
    out(d,s);
  }

  for(i=0;i<50;i++){
    n=rnd.next(MIN_digits_of_N,MAX_digits_of_N);
    sprintf(s,"51_random_large_%02d.in",i);
    MakeNum(n,d);
    out(d,s);
  }
    
  for(i=0;i<5;i++){
    n=MIN_digits_of_N;
    sprintf(s,"52_MIN_%02d.in",i);
    MakeNum(n,d);
    out(d,s);
  }
  
  for(i=0;i<10;i++){
    n=MAX_digits_of_N;
    sprintf(s,"53_MAX_%02d.in",i);
    MakeNum(n,d);
    out(d,s);
  }

  for(i=0;i<10;i++){
    sprintf(s,"54_51?3_%02d.in",i);
    strcpy(d,g);
    d[2]+=i;
    out(d,s);
  }

  for(i=0;i<10;i++){
    sprintf(s,"55_51?2_%02d.in",i);
    strcpy(d,g);
    d[2]+=i;
    d[3]--;
    out(d,s);
  }
  return 0;
}

  
