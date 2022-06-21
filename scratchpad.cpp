#include <iostream>
#include <regex>


inline bool NameMatchesRegexPattern(const std::string& name, const std::string& pattern) {
  return std::regex_match(name, std::regex(pattern));
}

int main() {
  std::cout << NameMatchesRegexPattern("ax0_ax1_fused_123", "((ax\\d_)+)fused_(\\d+)") << std::endl;

  return 0;
}
