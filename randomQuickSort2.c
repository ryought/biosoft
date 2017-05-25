#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
// 時間測定用

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

// Tail Recursion Elimination 再帰を取り除く
// スタックを消費しなくなる
void randomQuickSort2(int* target, int aLeft, int right) {
  int left = aLeft;
  while(left < right){
    int i = partition(target, left, right); // pivotの位置
    randomQuickSort2(target, left, i-1);
    left = i+1; 
  }
}

// 左右の長さで優先順位を変える
// 長い方を先に再帰呼び出しすると、短い方の再帰スタックが延々待たされる
// 短い方を先に再帰呼び出しすれば、短い方はすぐ終わるので、積まれるスタックの最大量は小さくなる
void randomQuickSort3(int* target, int aLeft, int aRight) {
  int left = aLeft; int right = aRight;
  while(left < right){
    int i = partition(target, left, right); // pivotの位置
    if(i-left <= right-i){ // left interval is shorter
      randomQuickSort3(target, left, i-1); // left first
      left = i+1;
    }else{
      randomQuickSort3(target, i+1, right);
      right = i-1;
    }
  }
}

// AをBに挿入する
void insert(int* target, int A, int B){
  int tmp = target[A];
  int i;
  for (i=A-1; i>=B; i--) {
    target[i+1] = target[i];
  }
  target[B] = tmp;
}


void insertionSort(int* target, int left, int right){
  int i, j;
  int tmp;
  for (i = left+1; i <= right; i++) {  // どこに行くかを決めてるもの    
    for (j = left; j < i; j++) {
      if (target[j] > target[i]) {
        insert(target, i, j);
        break;
      }
    }
  }
}

void randomQuickSort4(int* target, int aLeft, int aRight, int minSize) {
  int left = aLeft; int right = aRight;
  while(left + minSize < right){ // サイズ
    int i = partition(target, left, right); // pivotの位置
    if(i-left <= right-i){ // left interval is shorter
      randomQuickSort4(target, left, i-1, minSize); // left first
      left = i+1;
    }else{
      randomQuickSort4(target, i+1, right, minSize);
      right = i-1;
    }
  }
  // 短いものに関してはinsertionソート
  insertionSort(target, left, right);
}



void randomQuickSort5sub(int* target, int aLeft, int aRight, int minSize) {
  int left = aLeft; int right = aRight;
  while(left + minSize < right){ // サイズ
    int i = partition(target, left, right); // pivotの位置
    if(i-left <= right-i){ // left interval is shorter
      randomQuickSort5sub(target, left, i-1, minSize); // left first
      left = i+1;
    }else{
      randomQuickSort5sub(target, i+1, right, minSize);
      right = i-1;
    }
  }
}


// 最後に一回insertionする
void randomQuickSort5(int* target, int left, int right, int minSize) {
  randomQuickSort5sub(target, left, right, minSize);
  // 最後に挿入ソートする
  insertionSort(target, left, right);
}

void dumpArray(int* target, int size){
  for(int i=0; i<size; i++) {
    printf("%d ", target[i]);
  }
  printf("\n");
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
  //randomQuickSort1(target, 0, 11);
  insertionSort(target, 0, SIZE-1);
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  dumpArray(target, SIZE);
  
  return 0;
}
