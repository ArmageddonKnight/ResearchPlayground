#include <algorithm>
#include <vector>

struct Solution {
  std::vector<std::vector<int>> solutions;

  void climbStairsHelper(const int n, const int current_pos,
                         std::vector<int> &current_trace) {
    if (current_pos + 1 == n) {
      current_trace.push_back(1);
      solutions.push_back(current_trace);
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

  s.climbStairs(3);
  return 0;
}
