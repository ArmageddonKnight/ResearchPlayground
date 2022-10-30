#include <numeric>
#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  int pivotIndex(const std::vector<int> &nums) {
    int rhs = std::accumulate(nums.begin(), nums.end(), 0);
    int lhs = 0;
    for (size_t i = 0; i < nums.size(); ++i) {
      rhs -= nums[i];
      if (lhs == rhs) {
        return i;
      }
      lhs += nums[i];
    }
    return -1;
  }
};

int main() {
  
  return 0;
}
