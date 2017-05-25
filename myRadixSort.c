#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
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


void radixSort(int* target, int size){
  int* tmp = (int *)malloc(sizeof(int)*size);
  int base = 10;

  int max = target[0];
  int mDigit = 0;

  // 最大値の取得コード
  for(int a=1; a<size; a++){
    if(max < target[a]) max = target[a];
  }

  // 最大桁数の取得
  for(; max>0; mDigit++) { max = max/base; }
  printf("mDigit %d\n", mDigit);

  
  for(int digit=1; digit<=mDigit; digit++){
    // 表をつくる
    int C[base];
    memset(C, 0, sizeof(C));
    for(int i=0; i<size; i++){
      C[ getDigit(target[i], digit, base) ]++;
    }

    // 表の累積版をつくる
    int C2[base];
    C2[0] = C[0];
    for(int j=1; j<base; j++){
      C2[j] = C2[j-1] + C[j];
    }

    // 表に従って並び替える
    for(int k=size-1; k>=0; k--){
      tmp[--C2[ getDigit(target[k], digit, base) ]] = target[k];
    }

    for(int l=0; l<size; l++) {
      target[l] = tmp[l];
    }
  }
  free(tmp);
}



void dumpArray(int* target, int size){
  for(int i=0; i<size; i++) {
    printf("%d ", target[i]);
  }
  printf("\n");
}

int main() {
  struct timeval start, end;
  int SIZE = 10;
  int target[SIZE];
  int i;

  printf("%d\n", getDigit(123, 5, 10));

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
