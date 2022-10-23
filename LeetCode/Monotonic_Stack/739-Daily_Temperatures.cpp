#include <stack>

#include "../common_utilities.h"

class Solution {
public:
  std::vector<int> dailyTemperatures(const std::vector<int> &temperatures) {
    std::vector<int> ret(temperatures.size());
    std::stack<int> next_warmer_temperature_indices;

    next_warmer_temperature_indices.push(temperatures.size());

    for (int i = temperatures.size() - 1; i >= 0; --i) {
      int curr = temperatures[i];
      while (next_warmer_temperature_indices.top() != -1 &&
             temperatures[next_warmer_temperature_indices.top()] <= curr) {
        next_warmer_temperature_indices.pop();
      }
      ret[i] = next_warmer_temperature_indices.top() ==
                       static_cast<int>(temperatures.size())
                   ? 0
                   : (next_warmer_temperature_indices.top() - i);
      next_warmer_temperature_indices.push(i);
    }
    return ret;
  }
};

int main() {
  LOG(INFO) << Solution().dailyTemperatures({73, 74, 75, 71, 69, 72, 76, 73});

  return 0;
}
