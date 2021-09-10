#include <array>
#include <chrono>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <sstream>

struct A {
  virtual ~A() = default;
};

struct B : A {
};


int ExtractFirstIntFromString(const std::string& str) {
  static const char* const digits = "0123456789";
  const std::size_t first_digit_pos = str.find_first_of(digits);
  if (first_digit_pos != std::string::npos) {
    const std::size_t first_non_digit_pos_after_digit = str.find_first_not_of(digits, first_digit_pos);
    return std::stoi(
             str.substr(first_digit_pos,
                        first_non_digit_pos_after_digit != std::string::npos ?
                          first_non_digit_pos_after_digit - first_digit_pos :
                          first_non_digit_pos_after_digit)
                    );
  }
  return -1;
}

static inline int ExtractLastIntFromString(const std::string& str) {
  static const char* const digits = "0123456789";
  size_t last_index = str.find_last_not_of(digits);
  return std::stoi(str.substr(last_index + 1));
}


int main() {
  int ints = ExtractFirstIntFromString("123456_12354566_swkjrnwierjn_234");
  std::string func_name = "tvmgen_default_fused_nn_batch_matmul_1_0_kernel0";
  func_name = func_name.substr(0, func_name.find_last_of("_kernel") - 6);

  std::cout << ExtractLastIntFromString(func_name) << std::endl;

  std::cout << std::numeric_limits<int>().min() << " : "
            << std::numeric_limits<int>().max();

  return 0;
}
