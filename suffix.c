// suffix array implementation

#include <stdio.h>
#include <stdlib.h>


// やりたいこと
// SAの構築(o(n))
// 文字列中からqueryの始まる位置を返す


// index -> suffix
int *get_suffix(int *target, int i){
  return target + i*sizeof(int);
}

// iから始まるsuffixのプリント
// DONE
void print_suffix(int *target, int i){
  for(; target[i]>0; i++){
    printf("%d", target[i]);
  }
  printf("\n");
}


void print(int *target, int size){
  for(int i=0; i<size; i++){
    printf("%d", target[i]);
  }
  printf("\n");
}

/////////// 
// target -> suffix array
// using Larsson-Sadakane algorithm  o(nlogn)
// doubling法
// SA_h 同士の順序 それぞれのsuffix(h文字)のh+1文字目〜2h文字目の順序が決まれば
// h文字では決まらないが2h文字では決まるsuffixの大小が決まる
// そしてh+1文字目〜2h文字目の大小は、SA_hでi+hとj+hの大小を見ればいい。
int *suffix_array(int *target, int size){
  int *SA = (int *)malloc(sizeof(int)*size);
  for(int i=0; i<size; i++){
    SA[i] = target[i];
  }
  return SA;
}

////////////
// target -> suffix array
// Induced Sorting Algorithm  o(n)
// 大事な命題
// 1. SA中で、[aでLtype, aでStype、cでLtype、cでStype、...]と並んでる
// 2. Ltypeのsf = x + [自分より辞書順で若い、LかLMStypeのsf]
// 3. Lの右はLMSかL($をS(=LMS)にするのはそのため)(SだとしたらLMSになるはずだから)
// 4. Ltypeの定義: S[i] > S[i+1]
// 5. S[i:]<S[j:] <=> S[i]<S[j] or S[i]==S[j] and S[i+1:]<S[j+1:]
int *suffix_array_induce(int *S, int n){
  int *SA = (int *)malloc(sizeof(int)*n);
  int *t = (int *)malloc(sizeof(int)*n);

  // step0 0 = S-type, 1 = L-typeとする
  t[n-1] = 0;
  for(int i=n-2; 0 <= i; i--) {
    if(S[i] == S[i+1]) t[i] = t[i+1];
    else {
      if(S[i] < S[i+1]) t[i] = 0;
      else t[i] = 1;
    }
  }

  
}


// 二分探索で見つける
int *find(int *target, int *query){

}

// Burrows Wheeler Transformで見つける
int *findBWT(int *target, int *query){

}




int main(int argc, char* argv[]) {
  int S[] = {1,2,3,1,2,4,3,1,3,2,0};

  // 全suffixの列挙
  for(int i=0; i<10; i++){
    printf("%d: ", i);
    print_suffix(S, i);
  }

  // suffix array 構築
  int* SA = suffix_array(S, 10);

  // SAの表示
  print(SA, 10);

  
  
  return 0;
}
