#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  size_t minSubArrayLen(int target, const std::vector<int> &nums) {
    size_t ret = nums.size() + 1;

    int sum = 0;
    for (size_t i = 0, j = 0; j < nums.size();) {
      sum += nums[j++];
      while (sum >= target) {
        ret = std::min(ret, j - i);
        sum -= nums[i++];
      }
    }
    return ret % (nums.size() + 1);
  }
};

int main() {
  LOG(INFO) << Solution().minSubArrayLen(7, {2, 3, 1, 2, 4, 3});
  LOG(INFO) << Solution().minSubArrayLen(4, {1, 4, 4});
  LOG(INFO) << Solution().minSubArrayLen(11, {1, 1, 1, 1, 1, 1, 1, 1});

  return 0;
}
