#include <functional>
#include <queue>

#include "../common_utilities.h"

namespace std {

template<>
struct greater<ListNodePtr<int>> {
  bool operator()(const ListNodePtr<int>& lhs, const ListNodePtr<int>& rhs) {
    return lhs->content > rhs->content;
  }
};

}

class Solution {
public:
  List<int> mergeKLists(const List<List<int>> &lists) {

    // Key Ideas:
    //
    // - Main a HEAP data structure (i.e., priority_queue), and retrieve the
    //   smallest element one at a time.
    std::priority_queue<ListNodePtr<int>, std::vector<ListNodePtr<int>>,
                        std::greater<ListNodePtr<int>>>
        heap;
    for (auto node_ptr = lists.root; node_ptr != nullptr;
         node_ptr = node_ptr->children) {
      heap.push(node_ptr->content.root);
    }

    List<int> ret;
    ListNodePtr<int> heap_top = nullptr;

    while (!heap.empty()) {
      heap_top = heap.top();
      ret.append(heap_top->content);
      heap.pop();

      if (heap_top->children != nullptr) {
        heap.push(heap_top->children);
      }
    }
    return ret;
  }
};

int main() {
  List<List<int>> list{{1, 4, 5}, {1, 3, 4}, {2, 6}};

  LOG(INFO) << list;
  LOG(INFO) << Solution().mergeKLists(list);

  return 0;
}
