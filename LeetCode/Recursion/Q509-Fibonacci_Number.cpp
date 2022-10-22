#include "../common_utilities.h"

struct Solution {
  int workspace[31];

  bool initialized = false;

  void Init() {
    workspace[0] = 0;
    workspace[1] = 1;

    for (int i = 2; i < 31; ++i) {
      workspace[i] = workspace[i - 1] + workspace[i - 2];
    }
  }

  int fib(const int n) {
    if (!initialized) {
      initialized = true;
      Init();
    }
    return workspace[n];
  }
};

int main() {
  LOG(INFO) << Solution().fib(3);
  LOG(INFO) << Solution().fib(4);

  return 0;
}
