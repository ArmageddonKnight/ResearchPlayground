#include <algorithm>
#include <iostream>
#include <vector>

size_t getAreaOfMaximalSquare(const std::vector<std::vector<char>> &M) {
  if (M.empty()) {
    return 0;
  }
  size_t ret = 0, nrows = M.size(), ncols = M[0].size();
  std::vector<size_t> left_margins(ncols, 0), right_margins(ncols, ncols - 1),
      heights(ncols, 0);
  for (size_t i = 0; i < nrows; ++i) {
    size_t curr_left = 0, curr_right = ncols - 1;
    for (size_t j = 0; j < ncols; ++j) {
      if (M[i][j] == '1') {
        heights[j] += 1;
        left_margins[j] = std::max(left_margins[j], curr_left);
      } else {
        heights[j] = 0;
        left_margins[j] = 0;
        curr_left = j + 1;
      }
    }
    for (long j = static_cast<long>(ncols - 1); j >= 0; --j) {
      if (M[i][j] == '1') {
        right_margins[j] = std::min(right_margins[j], curr_right);
      } else {
        right_margins[j] = ncols - 1;
        curr_right = static_cast<size_t>(j) - 1;
      }
    }

    for (size_t j = 0; j < ncols; ++j) {
      ret =
          std::max(ret, (right_margins[j] - left_margins[j] + 1) * heights[j]);
    }
  }
  return ret;
}

int main() {
  std::cout << getAreaOfMaximalSquare({{'1', '0', '1', '0', '0'},
                                       {'1', '0', '1', '1', '1'},
                                       {'1', '1', '1', '1', '1'},
                                       {'1', '0', '0', '1', '0'}})
            << std::endl;
  return 0;
}