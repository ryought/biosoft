/**
関数の実行時間を調べる
**/
#include <stdio.h>
#include <sys/time.h>
#define SIZE 1000000
#define TRIAL 100

int main() {
  struct timeval start, end;
  
  
  // データの生成
  srand((unsigned) time(NULL));
  for(int k=0; k<SIZE; k++){
    target[k] = (rand()%1000);
  }

  for(int i=0; i<TRIAL; i++) {
    // define 

    
    gettimeofday(&start, NULL);

    // 時間測定対象の処理
    // FUNC();

    gettimeofday(&end, NULL);
  }
  printf("%ld\n",
	 (end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec));

  //dumpArray(target, SIZE);
  
  return 0;
}
