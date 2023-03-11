// #include <cstdio>

#include <iostream>
// #include <quik_fix/logging.h>
#include <regex>
#include <string>
// #include <quik_fix/logging_stl.h>

#include <map>
#include <set>
#include <unordered_map>

struct TimeStamp {
  int year;
  int month;
  int date;
  int hour;
  int minute;
  int second;
  bool operator<(const TimeStamp &other) const {
    if (year < other.year) {
      return true;
    }
    if (year > other.year) {
      return false;
    }
    if (month < other.month) {
      return true;
    }
    if (month > other.month) {
      return false;
    }
    if (date < other.date) {
      return true;
    }
    if (date > other.date) {
      return false;
    }
    if (hour < other.hour) {
      return true;
    }
    if (hour > other.hour) {
      return false;
    }
    if (minute < other.minute) {
      return true;
    }
    if (minute > other.minute) {
      return false;
    }
    if (second < other.second) {
      return true;
    }
    if (second > other.second) {
      return false;
    }
    return false;
  }
  bool operator==(const TimeStamp &other) const {
    return year == other.year && month == other.month && date == other.date &&
           hour == other.hour && minute == other.minute &&
           second == other.second;
  }
};

std::unordered_map<std::string, TimeStamp> string_to_time_stamp_cache;

struct CustomizedStringCmp {
  bool operator()(const std::string &lhs, const std::string &rhs) const {
    if (string_to_time_stamp_cache[lhs] < string_to_time_stamp_cache[rhs]) {
      // std::cout << lhs << " < " << rhs << std::endl;
      return true;
    }
    if (string_to_time_stamp_cache[lhs] == string_to_time_stamp_cache[rhs]) {
      if (lhs.size() < rhs.size()) {
        // std::cout << lhs << " << " << rhs << std::endl;
        return true;
      }
      if (lhs.size() == rhs.size()) {

        // for (size_t char_id = 0; char_id < lhs.size(); ++char_id) {
        //   if (lhs[char_id] < rhs[char_id]) {
        //     return true;
        //   }
        // }
        if (lhs < rhs) {
          // std::cout << lhs << " <<< " << rhs << std::endl;
          return true;
        }
      }
    }
    // std::cout << lhs << " > " << rhs << std::endl;
    return false;
  }
};

int main() {
  int num_strings;
  std::string input_string;

  std::cin >> num_strings;
  std::set<std::string, CustomizedStringCmp> sorted_string_maps;

  for (int str_id = 0; str_id < num_strings; ++str_id) {
    std::cin >> input_string;

    // QF_LOG_INFO << input_string;
    auto iter = string_to_time_stamp_cache.find(input_string);
    if (iter != string_to_time_stamp_cache.end()) {
      continue;
    }

    std::smatch sub_match;
    std::regex time_stamp_pattern(
        "[0-9]{4}-[0-9]{2}-[0-9]{2}T[0-9]{2}:[0-9]{2}:[0-9]{2}");
    // "[0-9]{4}");

    if (std::regex_search(input_string, sub_match, time_stamp_pattern)) {
      TimeStamp time_stamp;
      char sep;
      std::istringstream strin(sub_match[0]);
      strin >> time_stamp.year >> sep >> time_stamp.month >> sep >>
          time_stamp.date >> sep >> time_stamp.hour >> sep >>
          time_stamp.minute >> sep >> time_stamp.second;
      string_to_time_stamp_cache[input_string] = time_stamp;
      sorted_string_maps.insert(input_string);
      // QF_LOG_INFO << year << month << date << hour << minute << second;
    }
  }

  for (const std::string &str : sorted_string_maps) {
    std::cout << str << std::endl;
  }

  return 0;
}
