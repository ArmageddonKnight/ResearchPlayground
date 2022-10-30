#include <queue>
#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  std::vector<int>
  findOrder(const int numCourses,
            const std::vector<std::pair<int, int>> &prerequisites) {
    std::vector<std::vector<int>> G(numCourses);
    std::vector<int> ret, indegree(numCourses);

    // Construct the graph with nodes and edges.
    for (const std::pair<int, int> &pre : prerequisites) {
      G[pre.second].push_back(pre.first);
      indegree[pre.first]++;
    }

    // Use a worklist algorithm to traverse through the graph.
    std::queue<int> worklist;
    for (int i = 0; i < numCourses; i++) {
      if (indegree[i] == 0) {
        worklist.push(i);
      }
    }

    while (!worklist.empty()) {
      int worklist_item = worklist.front();
      worklist.pop();
      ret.push_back(worklist_item);
      for (const int nextCourse : G[worklist_item]) {
        --indegree[nextCourse];
        if (indegree[nextCourse] == 0) {
          worklist.push(nextCourse);
        }
      }
    }
    if (static_cast<int>(ret.size()) == numCourses) {
      return ret;
    }
    return {};
  }
};

int main() {
  LOG(INFO) << Solution().findOrder(4, {{1, 0}, {2, 0}, {3, 1}, {3, 2}});
  return 0;
}
