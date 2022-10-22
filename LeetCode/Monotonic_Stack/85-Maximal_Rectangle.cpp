#include <climits>
#include <stack>
#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  int largestRectangleArea(const std::vector<std::vector<int>> &matrix) {
    int ret = 0;
    size_t m = matrix.size(), n = matrix[0].size();
    std::vector<std::vector<int>> width_dp(m + 1, std::vector<int>(n + 1, 0)),
        prev_one_index(m, std::vector<int>(n, 1)),
        next_one_index(m, std::vector<int>(n, 1));
    for (int i = m - 1; i >= 0; --i) {
      for (int j = n - 1; j >= 0; --j) {
        width_dp[i][j] = matrix[i][j] ? width_dp[i][j + 1] + 1 : 0;
      }
    }

    std::stack<int> one_indices;
    for (size_t j = 0; j < n; j++) {
      one_indices = std::stack<int>();
      one_indices.push(-1);

      for (size_t i = 0; i < m; ++i) {
        while (one_indices.top() != -1 &&
               width_dp[one_indices.top()][j] >= width_dp[i][j]) {
          one_indices.pop();
        }
        prev_one_index[i][j] = one_indices.top();
        one_indices.push(i);
      }

      one_indices = std::stack<int>();
      one_indices.push(m);

      for (int i = m - 1; i >= 0; --i) {
        while (one_indices.top() != static_cast<int>(m) &&
               width_dp[one_indices.top()][j] >= width_dp[i][j]) {
          one_indices.pop();
        }
        next_one_index[i][j] = one_indices.top();
        one_indices.push(i);
      }
    }

    LOG(INFO) << "width_dp=" << width_dp
              << ", prev_one_index=" << prev_one_index
              << ", next_one_index=" << next_one_index;

    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        ret = std::max(ret, width_dp[i][j] * (next_one_index[i][j] -
                                              prev_one_index[i][j] - 1));
      }
    }

    return ret;
  }
};

int main() {
  LOG(INFO) << Solution().largestRectangleArea(
      {{1, 0, 1, 0, 0}, {1, 0, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 0, 0, 1, 0}});

  return 0;
}
