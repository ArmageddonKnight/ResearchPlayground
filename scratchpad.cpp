#include <iostream>
#include <vector>
#include <functional>

struct A {
  virtual void f() {
    std::cout << "A" << std::endl;
  }
};

struct B : A {
  void f() override {
    std::cout << "B" << std::endl;
  }
};

struct C : B {
  void f() override {
    std::cout << "C" << std::endl;
  }
};


int main() {
  A *a = new C();
  a->f();
  return 0;
}
