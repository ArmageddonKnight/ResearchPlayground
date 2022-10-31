#include <queue>
#include <unordered_set>
#include <vector>

#include "../common_utilities.h"

class Solution {
public:
  int ladderLength(const std::string &beginWord, const std::string &endWord,
                   const std::vector<std::string> &wordList) {

    // `unvisited_words` keeps track of which node has NOT been visited before.
    std::unordered_set<std::string> unvisited_words(wordList.begin(),
                                                    wordList.end());
    std::queue<std::string> worklist;

    worklist.push(beginWord);
    int ladder = 1;

    // The worklist algorithm.
    while (!worklist.empty()) {
      int n = worklist.size();

      // Note that here in the case of BFS, we keep popping the worklist until
      // there is no workitem left.
      for (int i = 0; i < n; ++i) {
        std::string word = worklist.front();
        worklist.pop();

        if (word == endWord) {
          return ladder;
        }
        unvisited_words.erase(word);
        for (size_t j = 0; j < word.size(); ++j) {
          char c = word[j];
          for (int k = 0; k < 26; ++k) {
            word[j] = 'a' + k;
            if (unvisited_words.find(word) != unvisited_words.end()) {
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

int main() {
  LOG(INFO) << Solution().ladderLength(
      "hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"});
  return 0;
}
