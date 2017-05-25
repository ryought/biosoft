#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

/* 共通 */
// arrayの中身の表示
void dumpArray(int* target, int size){
  for(int i=0; i<size; i++) {
    printf("%d ", target[i]);
  }
  printf("\n");
}



/* randomQuickSort
   ランダムクイックソート系*/

/* pivotをランダムに選択する */
int selectRandomPosition(int* target, int left, int right){
  srand((unsigned) time(NULL));
  return (rand() % (right-left+1)) + left;
}

/* targetのleft~rightをpivotより小,pivot,pivotより大に並び替える */
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

/* インサートソート用、A番目要素をB番目に挿入する、それ以外は全て平行移動する */
void insert(int* target, int A, int B){
  int tmp = target[A];
  int i;
  for (i=A-1; i>=B; i--) {
    target[i+1] = target[i];
  }
  target[B] = tmp;
}


/* インサートソート  再帰はしないから短い時は早い*/
void insertionSort(int* target, int left, int right){
  int i, j;
  for (i = left+1; i <= right; i++) {  // どこに行くかを決めてるもの    
    for (j = left; j < i; j++) {
      if (target[j] > target[i]) {
        insert(target, i, j);
        break;
      }
    }
  }
}

void insertionSort2(int* target, int left, int right){
  int tmp;
  for(int c = left+1; c <= right; c++) {
    int d = c;
    while (d>0 && target[d] < target[d-1]) {
      tmp = target[d]; target[d] = target[d-1]; target[d-1] = tmp;
      d--;
    }
  }
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

// 短い配列はインサートソートする
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


// randomQuickSort5用
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
  //insertionSort(target, left, right);
}


// 最後に一回insertionする
void randomQuickSort5(int* target, int left, int right, int minSize) {
  randomQuickSort5sub(target, left, right, minSize);
  // 最後に挿入ソートする
  insertionSort2(target, left, right);
}


// ternary Split Quick Sort用のパーティション関数
void splitPartition(int* target, int left, int right, int *A, int *B) {
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

  // 端に寄せておいたpivotと同じ値の要素を、中央に移動する
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
  // pivotより小さい値の集合の終わる位置、pivotより大きい値の集合の始まる位置をかえす
  *A = j;
  *B = i;
}

// Ternary Split Quick Sort
void ternarySplitQuickSort(int* target, int left, int right) {
  int i,j;
  if(left < right){
    splitPartition(target, left, right, &i, &j); // pivotの位置
    ternarySplitQuickSort(target, left, i);
    ternarySplitQuickSort(target, j, right);
  }
}





/* radixSort系 */
// Xのbase進法でいうpos桁目を取得する
int getDigit(int num, int pos, int base){
  int q = num;
  int r = 0;
  for(int i=0; i<pos; i++){
    r = q % base;
    q = q / base;
  }
  return r;
}

int digit(int num, int j, int m){
  int quotient = num;
  int remainder = 0;
  for(int i=0; i<j; i++){
    remainder = quotient % m;
    quotient = quotient/m;
  }
  return remainder;
}

// 授業スライドより
void radixSort(int* target, int targetLen, int m){
  int* tmp = (int *)malloc(sizeof(int) * targetLen);
  if(tmp == NULL) exit(1);

  int* count = (int *)malloc(sizeof(int) * m);

  // 配列内最大桁数の取得  配列内の最大値の桁数と同じ
  int max = target[0];
  for(int i=1; i<targetLen; i++){
    if(max<target[i]) max = target[i];
  }
  int maxDigit = 0;
  for(; max > 0; maxDigit++) { max = max/m; }

  // j桁目のソート
  for(int j=1; j<=maxDigit; j++){
    // 初期化
    for(int i=0; i<m; i++) { count[i] = 0; }

    for(int i=0; i<targetLen; i++){
      count[digit(target[i], j, m)]++;
    }
    for(int i=1; i<m; i++){
      count[i] = count[i-1]+count[i];
    }

    for(int i=targetLen-1; 0<=i; i--){
      tmp[  --count[ digit(target[i], j, m) ] ] = target[i];
    }

    for(int i=0; i<targetLen; i++) {
      target[i] = tmp[i];
    }
  }
  free(tmp);
  free(count);
}

// ふつうのradixsort
void myRadixSort(int* target, int size){
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


void radixSortMSDSub(int* target, int left, int right, int digit){
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
      radixSortMSDSub(target, left + C3[q]-C[q], left + C3[q]-1, digit-1);
    }
  }
}


// 最大桁からradixソートする
void radixSortMSD(int* target, int size){
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
  radixSortMSDSub(target, 0, size-1, mDigit);
}
