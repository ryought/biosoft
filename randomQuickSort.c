#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int selectRandomPosition(int* target, int left, int right){
  srand((unsigned) time(NULL));
  return (rand() % (right-left+1)) + left;
}


int partition(int* target, int left, int right) {
  int random = selectRandomPosition(target, left, right);
  int tmp=target[right]; target[right]=target[random]; target[random]=tmp;
  int pivot = target[right];
  int i = left-1;
  int j = right;

  for(;;){
    for(i++; target[i]<pivot; i++){}
    for(j--; pivot<target[j] && i<j; j--){}
    if(i>=j) break;
    tmp=target[i]; target[i]=target[j]; target[j]=tmp;
  }
  tmp=target[i]; target[i]=target[right]; target[right]=tmp;
  return i;
}


void randomQuickSort1(int* target, int left, int right) {
  if(left < right){
    int i = partition(target, left, right); // pivotの位置
    randomQuickSort1(target, left, i-1);
    randomQuickSort1(target, i+1, right);
  }
}

int main(){
  int target[12] = {48, 195, 12, 49, 198, 24, 99, 140, 48, 195, 12, 48};
  randomQuickSort1(target, 0, 11);
  int i;
  for(i=0; i<12; i++){
    printf("%d ", target[i]);
  }
  printf("\n");
  
  return 0;
}
