#include <iostream>
#include <memory>
#include <unordered_map>

#include <dmlc/logging.h>

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const std::vector<T> &v) {
  std::ostringstream strout;
  strout << "[";
  for (const T &item : v) {
    strout << item << ", ";
  }
  strout << "]";
  out << strout.str();
  return out;
}

template <typename K, typename V>
inline std::ostream &operator<<(std::ostream &out,
                                const std::unordered_map<K, V> &m) {
  std::ostringstream strout;
  strout << "{";
  for (const std::pair<const K, V> &item : m) {
    strout << item.first << " : " << item.second;
  }
  strout << "}";
  out << strout.str();
  return out;
}

template <typename T, const int TNumChildren> struct Node {
  T content;
  std::shared_ptr<Node> children[TNumChildren] = {nullptr};
};

template <typename T>
using ListNode = Node<T, 1>;

template <typename T>
using ListNodePtr = std::shared_ptr<ListNode<T>>;

template <typename T>
using BinaryTreeNode = Node<T, 2>;
