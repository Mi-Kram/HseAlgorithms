#include <iostream>
#include <set>
#include <vector>

int main() {
  std::set<int> set, set1, set2;

  int len;
  std::cin >> len;
  std::vector<int> arr1(len);

  for (int i = 0; i < len; i++) {
    std::cin >> arr1[i];
    set.insert(arr1[i]);
    set1.insert(arr1[i]);
  }

  std::cin >> len;
  std::vector<int> arr2(len);

  for (int i = 0; i < len; i++) {
    std::cin >> arr2[i];
    set.insert(arr2[i]);
    set2.insert(arr2[i]);
  }

  len = std::max(arr1.size(), arr2.size());
  arr1.resize(len, 0);
  arr2.resize(len, 0);

  std::set<int>::iterator curIt;
  for (auto it = set.begin(); it != set.end(); ) {
    curIt = it;
    ++it;
    if (set1.find(*curIt) == set1.end() || set2.find(*curIt) == set2.end()) set.erase(curIt);
  }
  
  if (set.empty()) {
    std::cout << "0 -1 -1";
    return 0;
  }

  int len1 = 0, pos1 = 0, cnt1 = 0;
  int len2 = 0, pos2 = 0, cnt2 = 0; 

  for (int i = 0; i < len; i++) {
    if (set.find(arr1[i]) == set.end()) { 
      if (len1 < cnt1) {
        pos1 = i - cnt1;
        len1 = cnt1;
      }
      cnt1 = 0;
    } else ++cnt1;

    if (set.find(arr2[i]) == set.end()) { 
      if (len2 < cnt2) {
        pos2 = i - cnt2;
        len2 = cnt2;
      }
      cnt2 = 0;
    } else ++cnt2;
  }

  if (len1 < cnt1) {
    pos1 = len - cnt1;
    len1 = cnt1;
  }

  if (len2 < cnt2) {
    pos2 = len - cnt2;
    len2 = cnt2;
  }

  len = std::min(len1, len2);
  std::cout << len << ' ' << (pos1 + 1) << ' ' << (pos2 + 1);

  return 0;
}