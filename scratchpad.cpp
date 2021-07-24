#include <iostream>
#include <vector>
#include <functional>


const struct A {
  int a;
  int b;
  int c;
  int d;
} a = {1, 2, 3, 4};


int main() {

  std::cout << a.a << std::endl;

  return 0;
}
