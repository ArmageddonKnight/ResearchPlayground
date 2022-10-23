#include <stack>

#include "../common_utilities.h"

class Solution {
public:
  std::vector<int> nextGreaterElements(const std::vector<int> &nums) {
    std::vector<int> ret(nums.size());
    std::stack<int> next_greater_indices;

    next_greater_indices.push(nums.size() * 2);

    for (int i = nums.size() * 2 - 1; i >= 0; --i) {
      while (next_greater_indices.top() != static_cast<int>(nums.size() * 2) &&
             nums[next_greater_indices.top() % nums.size()] <=
                 nums[i % nums.size()]) {
        next_greater_indices.pop();
      }
      ret[i % nums.size()] =
          next_greater_indices.top() == static_cast<int>(nums.size() * 2)
              ? -1
              : nums[next_greater_indices.top() % nums.size()];
      next_greater_indices.push(i);
    }
    return ret;
  }
};

int main() {
  LOG(INFO) << Solution().nextGreaterElements({1, 2, 1}) << ", "
            << Solution().nextGreaterElements({1, 2, 3, 4, 3});

  return 0;
}
