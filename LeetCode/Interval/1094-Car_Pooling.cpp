#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  bool carPooling(const std::vector<std::vector<int>> &trips, int capacity) {
    int stops[1001] = {};
    for (const std::vector<int> &t : trips) {
      stops[t[1]] += t[0], stops[t[2]] -= t[0];
    }
    for (auto i = 0; i < 1001; ++i) {
      capacity -= stops[i];
      if (capacity < 0) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  LOG(INFO) << Solution().carPooling({{2, 1, 5}, {3, 3, 7}}, 4);
  LOG(INFO) << Solution().carPooling({{2, 1, 5}, {3, 3, 7}}, 5);
  return 0;
}
