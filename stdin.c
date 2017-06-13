#include <stdio.h>

int main() {
  int *fp;
  char buf[1024];
  
  while(fgets(buf, 1023, stdin) != NULL){
    printf("(got) %s", buf);
  }
  return 0;
  
}
