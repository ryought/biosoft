#include <stdio.h>
#include <stdlib.h>

int mc(int n){
  printf("called %d \n", n);
  int i;
  if(n>100){
    i = n-10;
    printf("return %d\n", i);
    return i;
  }else{
    i = mc(mc(n+11));
    printf("return %d\n", i);
    return i;
  }
}


int main(int argc, char** argv) {
  printf("%d\n", mc(atoi(argv[1])));
  return 0;
}
