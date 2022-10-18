#include <initializer_list>
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

template <typename T, int TNumChildren> struct Node {
  T content;
  std::shared_ptr<Node> children[TNumChildren] = {nullptr};
};

/******************************************************************************
 * Linked List
 ******************************************************************************/

template <typename T> struct Node<T, 1> {
  T content;
  std::shared_ptr<Node> children = nullptr;
};

template <typename T> using ListNode = Node<T, 1>;

template <typename T> using ListNodePtr = std::shared_ptr<ListNode<T>>;

template <typename T> struct List {
  List() = default;
  List(std::initializer_list<T> init_list) {
    for (auto iter = init_list.begin(); iter != init_list.end(); ++iter) {
      append(*iter);
    }
  }
  void append(const T &item) {
    ListNode<T> node{.content = item};
    ListNodePtr<T> node_ptr = std::make_shared<ListNode<T>>(node);

    if (!root) {
      root = tail = node_ptr;
      return;
    }
    tail->children = node_ptr;
    tail = node_ptr;
  }
  ListNodePtr<T> root = nullptr, tail = nullptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const List<T> &list) {
  out << "[";
  for (auto node_ptr = list.root; node_ptr != nullptr;
       node_ptr = node_ptr->children) {
    out << node_ptr->content << ", ";
  }
  out << "]";
  return out;
}

template <typename T> using BinaryTreeNode = Node<T, 2>;
