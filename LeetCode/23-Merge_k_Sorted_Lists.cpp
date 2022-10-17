#include <initializer_list>

#include "common_utilities.h"

template <typename T> struct List {
  List(std::initializer_list<T> init_list) {
    ListNode<T> node{.content = *init_list.begin(), .children = {nullptr}};
    root = std::make_shared<ListNode<T>>(node);
    // for (auto iter = init_list.begin(); iter != init_list.end(); ++iter) {
    //   auto iter_copy = iter;
    //   if ((++iter_copy) == init_list.end()) {

    //   } else {
    //     root = std::make_shared(new ListNode{*iter, {root}});
    //   }
    // }
  }
  ListNodePtr<T> root;
};

int main() {
  List list{1, 2, 3, 4};

  LOG(INFO) << list.root->content;

  return 0;
}
