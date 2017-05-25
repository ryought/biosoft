#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define SIZE 10
// Xのbase進法でいうpos桁目を取得する
int getDigit(int num, int pos, int base){
  int q = num;
  int r = 0;
  //X/ (pow(pos-1)) 羃乗でやってもいいけど…
  for(int i=0; i<pos; i++){
    r = q % base;
    q = q / base;
  }
  return r;
}


void dumpArray(int* target, int size){
  for(int i=0; i<size; i++) {
    printf("%d ", target[i]);
  }
  printf("\n");
}

void radixSortSub(int* target, int left, int right, int digit){
  if(digit < 1){
    return;
  }

  if(right <= left){
    return;
  }

  int size = right - left + 1;
  
  int* tmp = (int *)malloc(sizeof(int)*size);
  for(int s=0; s<size; s++){
    tmp[s] = target[left+s];
  }
  int base = 10;

  // 表をつくる
  int C[base];
  memset(C, 0, sizeof(C));
  for(int i=0; i<size; i++){
    C[ getDigit(target[left+i], digit, base) ]++;
  }

  // 表の累積版をつくる
  int C2[base];
  C2[0] = C[0];
  for(int j=1; j<base; j++){
    // digit桁目がj以下の数はC2[j]個ふくまれてるよ！という配列
    C2[j] = C2[j-1] + C[j];
  }

  int C3[base];
  for(int f=0; f<base; f++){
    C3[f] = C2[f];
  }

  // 表に従って並び替える
  for(int k=size-1; k>=0; k--){
    target[--C2[ getDigit(tmp[k], digit, base) ] + left] = tmp[k];
  } 
  free(tmp);

  // 桁の数字の種類ごとに再帰呼び出し
  for(int q=0; q<base; q++) {
    if(C[q] > 1){
      radixSortSub(target, left + C3[q]-C[q], left + C3[q]-1, digit-1);
    }
  }
}



void radixSort(int* target, int size){
  int max = target[0];
  int mDigit = 0;

  int base = 10;

  // 最大値の取得コード
  for(int a=1; a<size; a++){
    if(max < target[a]) max = target[a];
  }

  // 最大桁数の取得
  for(; max>0; mDigit++) { max = max/base; }

  // 最大桁数からソート
  radixSortSub(target, 0, size-1, mDigit);
}





int main() {
  struct timeval start, end;
  int target[SIZE];

  srand((unsigned) time(NULL));
  for(int k=0; k<SIZE; k++){
    target[k] = (rand()%500);
  }

  dumpArray(target, SIZE);

  gettimeofday(&start, NULL);
  //randomQuickSort1(target, 0, 11);
  radixSort(target, SIZE);
  gettimeofday(&end, NULL);
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  dumpArray(target, SIZE);
  
  return 0;
}
