#include <stdio.h>

int call(int x) {
  return call(x+1);
}

int main() {
  printf("hoge");
  int x = call(0);
  return 0;
}
