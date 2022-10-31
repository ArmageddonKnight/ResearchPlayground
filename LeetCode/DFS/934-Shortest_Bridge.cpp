#include <queue>
#include <vector>

#include "../common_utilities.h"

class Solution {
private:
  std::vector<std::vector<int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  void dfs(std::vector<std::vector<int>> &grid, int x, int y,
           std::queue<std::pair<int, int>> &worklist) {
    int row = grid.size();
    int col = grid[0].size();
    worklist.push({x, y});
    grid[x][y] = 2;
    for (int i = 0; i < 4; i++) {
      int nx = x + dirs[i][0];
      int ny = y + dirs[i][1];
      if (nx >= 0 && ny >= 0 && nx < row && ny < col && grid[nx][ny] == 1) {
        dfs(grid, nx, ny, worklist);
      }
    }
  }

public:
  int shortestBridge(std::vector<std::vector<int>> &grid) {
    int row = grid.size();
    int col = grid[0].size();

    // First use DFS to populate the worklist with workitems of one island.
    std::queue<std::pair<int, int>> worklist;
    bool found = false;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (grid[i][j] == 1) {
          dfs(grid, i, j, worklist);
          found = true;
          break;
        }
      }
      if (found) {
        break;
      }
    }

    int level = 0;

    while (!worklist.empty()) {
      int size = worklist.size();
      for (int i = 0; i < size; i++) {
        std::pair<int, int> point = worklist.front();
        worklist.pop();
        int x = point.first;
        int y = point.second;

        for (int i = 0; i < 4; i++) {
          int nx = x + dirs[i][0];
          int ny = y + dirs[i][1];
          if (nx >= 0 && ny >= 0 && nx < row && ny < col) {
            if (grid[nx][ny] == 1) {
              return level;
            }
            if (grid[nx][ny] == 0) {
              grid[nx][ny] = 2;
              worklist.push({nx, ny});
            }
          }
        }
      }
      level++;
    }
    return -1;
  }
};

int main() { return 0; }