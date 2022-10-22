#include "../common_utilities.h"

template <typename T = int> struct TreeNode {
  T content;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;
};

struct Solution {
  bool hasPathSumHelper(TreeNode<int> *const root, const int targetSum,
                        const int currentSum) {
    if (!root) {
      return currentSum == targetSum;
    }
    return hasPathSumHelper(root->left, targetSum,
                            currentSum + root->content) ||
           hasPathSumHelper(root->right, targetSum, currentSum + root->content);
  }

  bool hasPathSum(TreeNode<int> *const root, const int targetSum) {
    return hasPathSumHelper(root, targetSum, 0);
  }
};

int main() {
  TreeNode<int> _1{2};
  TreeNode<int> _2{3};
  TreeNode<int> _3{1, &_1, &_2};

  LOG(INFO) << Solution().hasPathSum(&_3, 3);
  LOG(INFO) << Solution().hasPathSum(&_3, 5);

  return 0;
}
