#include "select.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(){
  int tmp;
  int N = 100000;
  int A[N], B[N];
  for(int i=0; i<N; i++){
    tmp = rand()%1000000;
    A[i] = tmp; B[i] = tmp;
  }
  struct timeval start, end;

  gettimeofday(&start, NULL);
  printf("%d\n", selectAve(A, N, 100));
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  gettimeofday(&start, NULL);
  printf("%d\n", selectWorse(B, N, 100));
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));
  return 0; 
}

