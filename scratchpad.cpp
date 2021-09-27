#include <random>
#include <vector>
#include <iostream>

int main() {

  std::uniform_real_distribution<> uniform_real_disb(0., 1.);
  std::mt19937 rng;

  std::vector<int> A(100);

  for (int& a : A) {
    a = uniform_real_disb(rng) < 0.8;
  }
  size_t cnt = 0;
  for (const int a : A) {
    if (a) {
      ++cnt;
    }
  }
  std::cout << cnt << std::endl;

  return 0;
}
