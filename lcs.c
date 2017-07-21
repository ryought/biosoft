#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int max(int a, int b) {
  if(a>b){
    return a;
  } else {
    return b;
  }
}

int get(int *arr, int i, int j){
  return arr[i*N+j]
}

int main() {
  //char* target = (char *)malloc(sizeof(char)*1*5);
  //target[0] = 'A';
  //target[1] = 'c';
  //target[2] = '\0';
  char A[14] = "acccagcagttaga";
  char B[14] = "atatgcgggatgcg";
  // printf("%s\n", target);
  int N = 14;
  int K = 14;
  int *c = (int *)malloc(sizeof(int)*N*K);

  for (int i=0; i<14; i++) {
    for (int j=0; j<14; j++) {
      if (i == 0 || j==0) {
        c[i*N + j] = 0;
      } else {
        if (A[i] == B[j]) {
          c[i*N + j] = max(0, c[(i-1)*N + (j-1)]+1);
        } else {
          c[i*N + j] = max(0, max(c[(i-1)*N + (j-1)], 
                           max(c[i*N + (j-1)], c[(i-1)*N + j])));
        }
      }
      printf("%d ", c[i*N+j]);
    }
    printf("\n");
  }
  return 0;
}
