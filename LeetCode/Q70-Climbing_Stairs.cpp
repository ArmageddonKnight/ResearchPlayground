#include <algorithm>
#include <vector>

#include "common_utilities.h"

struct Solution {
  std::vector<std::vector<int>> solutions;

  void climbStairsHelper(const int n, const int current_pos,
                         std::vector<int> &current_trace) {
    if (current_pos == n) {
      solutions.push_back(current_trace);
      LOG(INFO) << "Pushing solution=" << current_trace;
      return;
    } else if (current_pos > n) {
      return;
    }
    current_trace.push_back(1);
    climbStairsHelper(n, current_pos + 1, current_trace);
    current_trace.pop_back();
    current_trace.push_back(2);
    climbStairsHelper(n, current_pos + 2, current_trace);
    current_trace.pop_back();
  }

  std::vector<std::vector<int>> climbStairs(const int n) {
    solutions.clear();
    std::vector<int> current_trace = {};
    climbStairsHelper(n, 0, current_trace);
    return solutions;
  }
};

int main() {
  Solution s;

  s.climbStairs(10);
  return 0;
}
