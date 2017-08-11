#include <iostream>


//class Kitty {
//}


struct HOGE {
  int i;
  int j;
};

//int func() {

void swap(int &a, int &b) {
  int temp;
  temp = a; a = b; b = temp;
}


int main() {
  HOGE h;
  h.i = 10;
  h.j = 20;
  bool x = true;
  
  int a = 1;
  int* b = &a;
  a = 2;
  std::cout << *b << std::endl;

  int c = 1;
  int &d = c;
  c = 2;
  std::cout << d << std::endl;

  int A = 5, B = 10;
  swap(A, B);
  std::cout << A << B << std::endl;

  int* const p;
  int const * p;

  std::cout << "hogehoge" << 1 << "desu" << h.j;
  return 0;
}
