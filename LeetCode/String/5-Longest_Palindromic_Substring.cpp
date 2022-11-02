#include <string>

#include "../common_utilities.h"

class Solution {
private:
  int check(const std::string &s, int L, int R) {
    while (L >= 0 and R < static_cast<int>(s.size()) and s[L] == s[R]) {
      L--;
      R++;
    }
    return R - L - 1;
  }

public:
  std::string longestPalindrome(const std::string &s) {
    int ans = 0, st = 0;
    int n = s.size();

    for (int i = 0; i < n; ++i) {
      int len1 = check(s, i, i);
      int len2 = check(s, i, i + 1);

      int len = std::max(len1, len2);

      if (len > ans) {
        ans = len;
        st = i - (len - 1) / 2;
      }
    }
    return s.substr(st, ans);
  }
};

int main() {
  LOG(INFO) << Solution().longestPalindrome("Apple");

  std::string input_string("Apple");
  LOG(INFO) << input_string.substr(1, 3);
  LOG(INFO) << input_string.substr(1, 6);
  LOG(INFO) << input_string.substr(1, std::string::npos);

  return 0;
}
