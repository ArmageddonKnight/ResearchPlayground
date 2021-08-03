#include <iostream>
#include <memory>
#include <vector>

struct A {
  virtual ~A() = default;
};

struct B : A {
};

int main() {
  std::shared_ptr<A> a(new A());
  std::shared_ptr<B> b = std::dynamic_pointer_cast<B>(a);

  if (b) {
    std::cout << "Downcast is successful";
  } else {
    std::cout << "It is not";
  }
  std::cout << std::endl;

  return 0;
}
