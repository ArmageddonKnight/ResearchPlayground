#include <climits>
#include <stack>
#include <vector>

#include "../common_utilities.h"

class Solution {
private:
  std::vector<int> nextSmallerElementIndex(const std::vector<int> &heights) {
    std::stack<int> lt_curr_indices;
    std::vector<int> ret(heights.size());
    lt_curr_indices.push(heights.size());

    for (int i = heights.size() - 1; i >= 0; --i) {
      int curr = heights[i];
      while (lt_curr_indices.top() != static_cast<int>(heights.size()) &&
             heights[lt_curr_indices.top()] >= curr) {
        lt_curr_indices.pop();
      }
      ret[i] = lt_curr_indices.top();
      lt_curr_indices.push(i);
    }
    return ret;
  }

  std::vector<int> prevSmallerElementIndex(const std::vector<int> &heights) {
    std::stack<int> lt_curr_indices;
    std::vector<int> ret(heights.size());
    lt_curr_indices.push(-1);

    for (int i = 0; i < static_cast<int>(heights.size()); ++i) {
      int curr = heights[i];
      while (lt_curr_indices.top() != -1 &&
             heights[lt_curr_indices.top()] >= curr) {
        lt_curr_indices.pop();
      }
      ret[i] = lt_curr_indices.top();
      lt_curr_indices.push(i);
    }
    return ret;
  }

public:
  int largestRectangleArea(const std::vector<int> &heights) {
    int n = heights.size();
    // Storing next and previous smaller element index
    const std::vector<int> next = nextSmallerElementIndex(heights),
                           prev = prevSmallerElementIndex(heights);

    LOG(INFO) << "next=" << next << ", prev=" << prev;

    int ret = INT_MIN;
    for (int i = 0; i < n; i++) {
      ret = std::max(ret, heights[i] * (next[i] - prev[i] - 1));
    }
    return ret;
  }
};

int main() {
  LOG(INFO) << Solution().largestRectangleArea({2, 1, 5, 6, 2, 3});

  return 0;
}
