#include <stdio.h>
#include <stdlib.h>

int multiply(int a, int b){
  int i;
  if(a>0)
    return (multiply((a-1),b) + b);
  else
    return 0;
}

int main(int argc, char** argv){
  printf("%d\n", multiply(atoi(argv[1]), atoi(argv[2])));
  return 0;
}
