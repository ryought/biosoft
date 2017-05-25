#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int selectRandomPosition(int* target, int left, int right){
  srand((unsigned) time(NULL));
  return (rand() % (right-left+1)) + left;
}

void dumpArray(int* target, int size){
  for(int dispPos=0; dispPos<size; dispPos++){
    printf("%d ", target[dispPos]);
  }
  printf("\n");
}


void partition(int* target, int left, int right, int *A, int *B) {
  int random = selectRandomPosition(target, left, right);
  int tmp=target[right]; target[right]=target[random]; target[random]=tmp;
  int pivot = target[right];
  int i = left-1;
  int j = right;

  // pivotと同じ値を左右に寄せておく
  int mi = left;
  int mj = right-1; // pivot値が始まる位置

  for(;;){
    // 並びがおかしいところで止まる
    for(i++; target[i]<=pivot && i<right ; i++){
      if(target[i]==pivot){
        if(i==mi) {
          mi++;
        }else{
          // pivotと同じ値を途中に発見
          tmp=target[i]; target[i]=target[mi]; target[mi]=tmp; // 入れ替え
          mi++; // miをインクリメント
        }
      }
    }
    for(j--; pivot<=target[j] && left<j; j--){
      // ここのi<jを抜かすと上手くいく 理由？？
      if(target[j]==pivot){
        if(j==mj){
          mj--;
        }else{
          tmp=target[j]; target[j]=target[mj]; target[mj]=tmp;
          mj--;
        }
      }
    }

    if(i>=j) break;

    if(i<j && target[i]!=pivot && target[j]!=pivot && target[i]!=target[j]){
      tmp=target[i]; target[i]=target[j]; target[j]=tmp;
    }
  }

  
  while(left < mi){
    mi--;
    tmp=target[mi]; target[mi]=target[j]; target[j]=tmp;
    j--;
  }
  while(mj < right){
    mj++;
    tmp=target[mj]; target[mj]=target[i]; target[i]=tmp;
    i++;
  }
  *A = j;
  *B = i;
}


void ternarySplitQuickSort(int* target, int left, int right) {
  int i,j;
  if(left < right){
    partition(target, left, right, &i, &j); // pivotの位置
    ternarySplitQuickSort(target, left, i);
    ternarySplitQuickSort(target, j, right);
  }
}

int main(){
  struct timeval start, end;
  int SIZE = 100;
  int target[SIZE];
  int i;

  srand((unsigned) time(NULL));
  for(int k=0; k<SIZE; k++){
    target[k] = (rand()%500);
  }

  dumpArray(target, SIZE);


  gettimeofday(&start, NULL);
  ternarySplitQuickSort(target, 0, SIZE-1);
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  dumpArray(target, SIZE);
  
  return 0; 
}
