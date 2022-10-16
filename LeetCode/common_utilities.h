#include <iostream>
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
