#include "sort.h"
#include <stdio.h>
#include <sys/time.h>
#define SIZE 1000000

int main() {
  struct timeval start, end;
  int target[SIZE];

  srand((unsigned) time(NULL));
  for(int k=0; k<SIZE; k++){
    target[k] = (rand()%1000);
  }

  //dumpArray(target, SIZE);

  gettimeofday(&start, NULL);

  //randomQuickSort(target, 0, SIZE-1);
  randomQuickSort5(target, 0, SIZE-1, 10);
  //radixSort(target, SIZE, 10);
  
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  //dumpArray(target, SIZE);
  
  return 0;
}
