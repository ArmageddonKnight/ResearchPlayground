#include <iostream>
#include <cassert>
#include <type_traits>


template<typename C>
struct A {
};

// template<typename TrueKing>
// struct GetValue {
//   static constexpr int value = 1;
// };

// template<>
// struct GetValue<int> {
//   static constexpr int value = 1;
// };


// int g();

template<>
struct [[deprecated("HappyHappy")]] A<int> {
  // void f() {
  //   // assert(false && "This should NOT happen");
  //   // static_assert(GetValue<int>::value, "Happy");
  //   // static_assert(std::is_same<int, int>::value, "Happy");
  //   g();
  // }
  // int a = g(3);
  static constexpr int a = 3;
};

template<typename C>
struct B : public A<C> {
  using A<C>::a;
};

int main() {
  struct A<float> a;
  struct B<int> b;
  // a.f();
  [[deprecated]] int d;

  std::cout << d << std::endl;

  return 0;
}
