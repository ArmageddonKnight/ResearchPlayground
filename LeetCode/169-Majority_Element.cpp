#include "common_utilities.h"

struct Solution {

  int majorityElement(const std::vector<int> &array) {
    // Boyer-Moore Majority Vote Algorithm
    // http://www.cs.utexas.edu/~moore/best-ideas/mjrty/

    int majority = array[0], count = 1;
    for (size_t i = 1; i < array.size(); i++) {
      if (count == 0) {
        count++;
        majority = array[i];
      } else if (majority == array[i]) {
        count++;
      } else {
        count--;
      }
    }
    return majority;
  }
};

int main() { 
  LOG(INFO) << Solution().majorityElement({1, 2, 1, 3, 1, 1, 2, 1, 5});

  return 0;
}
