// #include <cstdio>

#include <iostream>
// #include <quik_fix/logging.h>
#include <string>
// #include <quik_fix/logging_stl.h>

inline bool isLunarYear(const int yr) {
  if (yr % 400 == 0) {
    return true;
  }
  if (yr % 4 == 0 && yr % 100 != 0) {
    return true;
  }
  return false;
}

inline int getNumberOfDaysByMonth(const int yr, const int mt) {
  if (mt == 1 || mt == 3 || mt == 5 || mt == 7 || mt == 8 || mt == 10 ||
      mt == 12) {
    return 31;
  } else if (mt == 4 || mt == 6 || mt == 9 || mt == 11) {
    return 30;
  }
  return isLunarYear(yr) ? 29 : 28;
}

int main() {
  int year, month, week, day;

  // std::string line;
  // std::getline(std::cin, line);
  while (std::cin >> year >> month >> week >> day) {
    int days_passed = 0;
    for (int yr = 2000; yr < year; ++yr) {
      days_passed += isLunarYear(yr) ? 366 : 365;
    }
    for (int mt = 1; mt < month; ++mt) {

      days_passed += getNumberOfDaysByMonth(year, mt);
    }

    // QF_LOG_INFO << days_passed;

    int new_day_at_new_month = (5 + days_passed) % 7 + 1;
    int date = 1;

    // QF_LOG_INFO << new_day_at_new_month;

    if (week == 1 && day < new_day_at_new_month) {
      // QF_LOG_INFO << "Here";
      std::cout << 0;
      continue;
    }
    if (week == 1) {
      date += day - new_day_at_new_month;
    } else {
      date += 7 - new_day_at_new_month;
      for (int wk = 2; wk < week; ++wk) {
        date += 7;
      }
      date += day;
    }

    if (date > getNumberOfDaysByMonth(year, month)) {
      // QF_LOG_INFO << "Here";
      std::cout << 0;
      continue;
    }
    std::cout << year << "-";
    if (month < 10) {
      std::cout << '0';
    }
    std::cout << month << "-";
    if (date < 10) {
      std::cout << '0';
    }
    std::cout << date;
    // size_t days_passed_since_starting_point = (year - 2000) * +
  }

  return 0;
}
