#include <fstream>
#include <iostream>

#include "../utils/counted-string.h"
#include "../utils/counted-time.h"
#include "../utils/mergesort.h"
#include "../utils/quicksort.h"
#include "../utils/string-generator.h"
#include "../utils/string-sort-tester.h"
#include "../utils/ternary-string-quicksort.h"
#include "../utils/string-mergesort-lcp.h"
#include "../utils/msd-radix-sort.h"
#include "../utils/msd-radix-sort-with-quick.h"

void stage2(std::string* random, std::string* reverseSorted, std::string* almostSorted);
void stage3(std::string* random, std::string* reverseSorted, std::string* almostSorted);
void combine_data(const char* path1, const char* path2, const char* resultPath);

int main() {
  StringGenerator gen(10, 200, 3000);

  std::string* random = gen.generateRandomArray();
  std::string* reverseSorted = gen.generateReversedArray();
  std::string* almostSorted = gen.generateAlmostSortedArray();

  // Выполнение этапа #2.
  stage2(random, reverseSorted, almostSorted);

  // Выполнение этапа #3.
  stage3(random, reverseSorted, almostSorted);

  delete[] random;
  delete[] reverseSorted;
  delete[] almostSorted;

  combine_data("stage2.txt", "stage3.txt", "data.txt");

  std::cout << "Finished successful";
  return 0;
}

void stage2(std::string* random, std::string* reverseSorted, std::string* almostSorted) {
  std::ofstream of("stage2.txt");
  if (!of) {
    std::cout << "stage2: ofstream error";
    return;
  }

  StringSortTester tester;

  of << "array length" << ';'
    << "random quicksort time" << ';'<< "random quicksort comparison" << ';'
    << "random mergesort time" << ';'<< "random mergesort comparison" << ';'
    << "reverseSorted quicksort time" << ';'<< "reverseSorted quicksort comparison" << ';'
    << "reverseSorted mergesort time" << ';'<< "reverseSorted mergesort comparison" << ';'
    << "almostSorted quicksort time" << ';'<< "almostSorted quicksort comparison" << ';'
    << "almostSorted mergesort time" << ';'<< "almostSorted mergesort comparison" << '\n';
  
  try {
    for (int i = 100; i <= 3000; i += 100) {
      SortReport r1 = tester.run(random, i, quicksort);
      SortReport r2 = tester.run(random, i, mergesort);

      SortReport r3 = tester.run(reverseSorted, i, quicksort);
      SortReport r4 = tester.run(reverseSorted, i, mergesort);

      SortReport r5 = tester.run(almostSorted, i, quicksort);
      SortReport r6 = tester.run(almostSorted, i, mergesort);

      of << i << ';'
        << r1.time << ';'<< r1.comparison << ';' << r2.time << ';' << r2.comparison << ';'
        << r3.time << ';'<< r3.comparison << ';' << r4.time << ';' << r4.comparison << ';'
        << r5.time << ';'<< r5.comparison << ';' << r6.time << ';' << r6.comparison << '\n';
    }

    of.flush();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  of.close();
}

void stage3(std::string* random, std::string* reverseSorted, std::string* almostSorted) {
  std::ofstream of("stage3.txt");
  if (!of) {
    std::cout << "stage3: ofstream error";
    return;
  }

  StringSortTester tester;

  of << "array length" << ';'

    << "random string_quicksort time" << ';'<< "random string_quicksort comparison" << ';'
    << "random string_mergesort time" << ';'<< "random string_mergesort comparison" << ';'
    << "random msd_radix_sort time" << ';'<< "random msd_radix_sort comparison" << ';'
    << "random msd_radix_sort_with_quick time" << ';'<< "random msd_radix_sort_with_quick comparison" << ';'

    << "reverseSorted string_quicksort time" << ';'<< "reverseSorted string_quicksort comparison" << ';'
    << "reverseSorted string_mergesort time" << ';'<< "reverseSorted string_mergesort comparison" << ';'
    << "reverseSorted msd_radix_sort time" << ';'<< "reverseSorted msd_radix_sort comparison" << ';'
    << "reverseSorted msd_radix_sort_with_quick time" << ';'<< "reverseSorted msd_radix_sort_with_quick comparison" << ';'

    << "almostSorted string_quicksort time" << ';'<< "almostSorted string_quicksort comparison" << ';'
    << "almostSorted string_mergesort time" << ';'<< "almostSorted string_mergesort comparison" << ';'
    << "almostSorted msd_radix_sort time" << ';'<< "almostSorted msd_radix_sort comparison" << ';'
    << "almostSorted msd_radix_sort_with_quick time" << ';'<< "almostSorted msd_radix_sort_with_quick comparison" << '\n';
  
  try {
    for (int i = 100; i <= 3000; i += 100) {
      SortReport r1 = tester.run(random, i, ternary_string_quicksort);
      SortReport r2 = tester.run(random, i, string_mergesort_lcp);
      SortReport r3 = tester.run(random, i, msd_radix_sort);
      SortReport r4 = tester.run(random, i, msd_radix_sort_with_quick);

      SortReport r5 = tester.run(reverseSorted, i, ternary_string_quicksort);
      SortReport r6 = tester.run(reverseSorted, i, string_mergesort_lcp);
      SortReport r7 = tester.run(reverseSorted, i, msd_radix_sort);
      SortReport r8 = tester.run(reverseSorted, i, msd_radix_sort_with_quick);

      SortReport r9 = tester.run(almostSorted, i, ternary_string_quicksort);
      SortReport r10 = tester.run(almostSorted, i, string_mergesort_lcp);
      SortReport r11 = tester.run(almostSorted, i, msd_radix_sort);
      SortReport r12 = tester.run(almostSorted, i, msd_radix_sort_with_quick);

      of << i << ';'
        << r1.time << ';'<< r1.comparison << ';' << r2.time << ';' << r2.comparison << ';'
        << r3.time << ';'<< r3.comparison << ';' << r4.time << ';' << r4.comparison << ';'
        << r5.time << ';'<< r5.comparison << ';' << r6.time << ';' << r6.comparison << ';' 
        << r7.time << ';'<< r7.comparison << ';' << r8.time << ';' << r8.comparison << ';' 
        << r9.time << ';'<< r9.comparison << ';' << r10.time << ';' << r10.comparison << ';' 
        << r11.time << ';'<< r11.comparison << ';' << r12.time << ';' << r12.comparison << '\n';
    }

    of.flush();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  of.close();


  delete[] random;
  delete[] reverseSorted;
  delete[] almostSorted;
}

void combine_data(const char* stage2Path, const char* stage3Path, const char* resultPath) {
  std::ifstream s1(stage2Path);
  std::ifstream s2(stage3Path);
  std::ofstream res(resultPath);

  if (!s1 || !s2 || !res) {
    std::cout << "combine_data: stream failed\n";
  }

  std::string line1, line2;
  while (std::getline(s1, line1) && std::getline(s2, line2)) {
    if (line1.empty() || line2.empty()) continue;
    res << line1 << line2.substr(line2.find(';')) << '\n';
  }

  res.flush();
  s1.close();
  s2.close();
  res.close();
}
