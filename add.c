/**
 csv stdin adder example
  cat hoge.csv | ./a.out 
**/
#include <stdio.h>

int main() {
  char buf[1024];
  int A, B, C;
  int sA, sB, sC;
  
  while(fgets(buf, sizeof(buf), stdin)){
    if(buf[0] == '#') continue;
    if(sscanf(buf, "%d , %d , %d", &A, &B, &C) == 3){
      sA = sA + A;
      sB = sB + B;
      sC = sC + C;      
    }
  }
  printf("%d %d %d\n", sA, sB, sC);
  return 0;
}
