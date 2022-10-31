#include <queue>
#include <unordered_set>
#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  int ladderLength(const std::string &beginWord, const std::string &endWord,
                   const std::vector<std::string> &wordList) {

    // `dict` keeps track of which node has been visited before.
    std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
    std::queue<std::string> worklist;

    worklist.push(beginWord);
    int ladder = 1;

    // The worklist algorithm.
    while (!worklist.empty()) {
      int n = worklist.size();

      // Note that here in the case of BFS, we keep popping the worklist until
      // there is no workitem left.
      for (int i = 0; i < n; i++) {
        std::string word = worklist.front();
        worklist.pop();

        if (word == endWord) {
          return ladder;
        }
        dict.erase(word);
        for (int j = 0; j < word.size(); j++) {
          char c = word[j];
          for (int k = 0; k < 26; k++) {
            word[j] = 'a' + k;
            if (dict.find(word) != dict.end()) {
              worklist.push(word);
            }
          }
          word[j] = c;
        }
      }
      ladder++;
    }
    return 0;
  }
};

int main() { return 0; }
