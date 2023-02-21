#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

size_t getLengthOfLongestSubstring(const std::string &input_str) {
  size_t ret = 0;
  std::unordered_map<char, size_t> char_to_substr_begin;

  size_t curr_substr_begin = 0;
  for (size_t input_str_id = 0; input_str_id < input_str.size();
       ++input_str_id) {
    size_t &substr_begin = char_to_substr_begin[input_str[input_str_id]];
    curr_substr_begin = std::max(curr_substr_begin, substr_begin);
    ret = std::max(ret, input_str_id - curr_substr_begin + 1);
    substr_begin = input_str_id + 1;
  }
  return ret;
}

int main() {
  std::cout << getLengthOfLongestSubstring("abcabcbb") << "\n";
  std::cout << getLengthOfLongestSubstring("bbbbb") << "\n";
  std::cout << getLengthOfLongestSubstring("pwwkew") << "\n";
  return 0;
}
