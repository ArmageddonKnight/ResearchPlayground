#include <iostream>
#include <vector>

template<typename T>
inline std::vector<size_t> UnpackVectorShape(const std::vector<T>& vec) {
  return {vec.size()};
}

template<typename T>
inline std::vector<size_t> UnpackVectorShape(const std::vector<std::vector<T>>& vec) {
  std::vector<size_t> subvec_shape = UnpackVectorShape(vec[0]);
  subvec_shape.insert(subvec_shape.begin(), vec.size());
  return subvec_shape;
}

int main() {
  std::vector<std::vector<std::vector<int>>> A(3, std::vector<std::vector<int>>(4, std::vector<int>(5, 0)));

  std::vector<size_t> shape = UnpackVectorShape(A);
  std::cout << shape.size() << std::endl;
  std::cout << "[";
  for (const auto& i : shape) {
    std::cout << i << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}