#include "sort.h"
#include <stdlib.h>
#include <time.h>

/* 平均計算量がO(n)となるSELECT  selectAve */

int selectAve(int* target, int targetLen, int k){
  if( k<0 || k>=targetLen-1 ) exit(1);
  int i;
  int left = 0;
  int right = targetLen-1;
  while((i=partition(target, left, right)) != k){ // sort.hのquicksortの関数そのまま
    if(i<k){
      // k番目の値は、targetのi~にある
      left = i+1;
      right = right;
    }else{
      // k番目の値は、targetの~iにある
      left = left;
      right = i-1;
    }
  }
  return target[k]; // target[i]がk番目の値
}





/****************************/
/* 最悪計算量がO(n)となるselect sel */
/****************************/

void swap(int *a, int *b){
  int tmp;
  tmp = *a; *a = *b; *b = tmp;
}


// target[l..r] から xを探して、xより大きい要素と小さい要素に分ける
int part(int* target, int l, int r, int x){
  // xを末尾に退避 targetのうちxを探して、後ろに寄せる
  int i;
  for(i=l; i<=r; i++){
    if(target[i] == x) break;
  }
  swap(&target[i], &target[r]);

  // quickソートのパクリ
  i = l;
  for(int j=l; j <= r-1; j++) {
    if(target[j] <= x){
      swap(&target[i], &target[j]);
      i++;
    }
  }

  // 最後に境目にxを戻す
  swap(&target[i], &target[r]);
  
  // xのある位置を返す
  return i;
}


// l~rをソートする
void sort(int* target, int l, int r){
  insertionSort(target, l, r);
}

// target[l,r]の、ソートした時のk番目(0から始まる)要素を返す
int sel(int* target, int l, int r, int k){
  // 配列長
  int n = r-l+1;

  if(n <= 5) {
    // 5個以下だったら分割する必要なし。
    sort(target, l, r);
    return target[l+k]; //ソート済みのうちのkを返す
    
  } else {
    // 5個以上だったら、グループに分割する
    // グループの中央値をmに格納
    int m[(n+4)/5]; // medians グループ数はceil(n/5)
    int i;
    for(i=0; i<n/5; i++) {
      m[i] = sel(target, l+5*i, l+5*(i+1)-1, 5/2); // 5個のグループの2番目が中央値
    }
    if(5*(i+1)-1 < r) {
      m[i] = sel(target, l+5*(i+1), r, (r - 5*i +1)/2); // あまりの分を格納。中央値はN/2番目の要素を取れば良い。
    }

    // グループの中央値の中央値を計算
    int mofm = sel(m, 0, (n+4)/5 - 1, ((n+4)/5)/2);

    // グループ内の分割作業。mofm以上か以下かで分けて、そのインデックスを見つける
    int p = part(target, l, r, mofm);

    // 次に探す部分を決める
    if (p - l == k)
      return target[p];
    else if (p - l > k)
      return sel(target, l, p-1, k);
    else
      return sel(target, p+1, r, k-p+l-1);
  }
}

int selectWorse(int* target, int targetLen, int k) {
  return sel(target, 0, targetLen - 1, k);
}
