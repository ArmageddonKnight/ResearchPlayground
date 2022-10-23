#include "../common_utilities.h"

class Solution {
public:
  std::vector<int> capitals;

#define C_CAPITAL_IDENTIFIER -1

  int capitalOf(const int city) {
    if (capitals[city] == C_CAPITAL_IDENTIFIER) {
      return city;
    }
    return capitals[city] = capitalOf(capitals[city]);
  }

  void U(const int city_a, const int city_b) {
    const int capital_a = capitalOf(city_a), capital_b = capitalOf(city_b);

    if (capital_a == capital_b) {
      return;
    }
    capitals[capital_a] = capital_b;
  }

  int findCircleNum(const std::vector<std::vector<int>> &M) {
    int n = M.size();
    capitals = std::vector<int>(n, C_CAPITAL_IDENTIFIER);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (M[i][j]) {
          U(i, j);
        }
      }
    }

    int c = 0;

    for (int i = 0; i < n; i++) {
      if (capitals[i] == C_CAPITAL_IDENTIFIER) {
        c++;
      }
    }
    return c;
  }
};

int main() {
  return 0;
}
