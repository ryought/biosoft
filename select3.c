// https://github.com/manishc1/Coding/blob/4f7195079f31e61dfe52644b849f3844fe3f3add/C/Search/Median_Of_Median.c
// 動かない 
#include "sort.h"
#include <stdio.h>

// selects the median of medians in an array
// @return idx
int sel(int *a, int s, int e, int k){
  // もしサイズが5以下だったら、ソートして、その順番を返す。中央値はk=3のとき
  if(e-s+1 <= 5){
    insertionSort(a, s, e);
    return s+k-1;
  }
  

  int* medians = (int *)malloc( sizeof(int) *  ((e-s)/5 + 1) );
  if(medians == NULL) exit(1);
    
  // if array is bigger
  // 5個単位の小グループに分け、その中の中央値を取り出す
  // 要素数はe-s+1個なので、グループ数は(e-s+1 + 4)/5 切り上げ 個
  // 目標としてはその中央値の中央値を調べたい。
    // and keep putting the medians in the starting of the array
  for(int i=0; i<(e-s)/5 + 1; i++){
    int left = 5*i;
    int right = left + 4;
    if(right > e) right = e;
    medians[i] = sel(a, left, right, 3);
    //swap(a[median], a[i]);
    //tmp = a[median]; a[median] = a[i]; a[i] = tmp;
  }

  int groupnum = (e-s)/5 + 1;
  int mofm = sel(medians, 0, groupnum, groupnum/2); // median of medians

  int* newa = (int *)malloc( sizeof(int) *  (e-s+1) );
  if(newa == NULL) exit(1);

  for(int i=0; i<groupnum; i++){
    if(medians[i]>medians[mofm]){
      
    }else{
      
    } 
  }
  
  return sel(a, 0, (e+1)/5, (e+1)/10);
}

int main(){
  int a[] = {6,7,8,1, 2, 3};
  int n = 6;
    
  int mom = sel(a, 0, n-1, 2);
    
  //cout<<"Median of Medians: " << a[mom] << endl;
  printf("median of medians: %d\n", a[mom]);
  return 0;
}
