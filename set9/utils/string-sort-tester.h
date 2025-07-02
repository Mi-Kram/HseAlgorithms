#ifndef STRING_SORT_TESTER_H
#define STRING_SORT_TESTER_H

#include <string>
#include <vector>

#include "./counted-string.h"
#include "./counted-time.h"

struct SortReport {
  long long time, comparison;
};


class StringSortTester {
 public:
  SortReport run(std::string* arr, int n, void(*sort)(CountedString*, CountedString*));
};

SortReport StringSortTester::run(std::string* arr, int n, void(*sort)(CountedString*, CountedString*)) {
  SortReport report{0, 0};

  for (int i = 0; i < 50; ++i) {
    CountedString* copy = new CountedString[n];
    for (int i = 0; i < n; ++i) copy[i] = &arr[i];

    CountedString::totalCharComparisons = 0;

    CountedTime timer;
    sort(copy, copy + n);
    long long time = timer.end();

    report.time += time;
    report.comparison += CountedString::totalCharComparisons;

    delete[] copy;
  }

  report.time /= 50;
  report.comparison /= 50;
  
  return report;
}

#endif
