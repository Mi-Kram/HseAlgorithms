#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  string s;
  getline(cin, s);

  unordered_map<string, int> dictionary;
  for (int i = 0; i < 128; ++i) {
    dictionary[string(1, char(i))] = i;
  }

  vector<int> output;
  string w;
  int next_code = 128;

  for (char c : s) {
    string wc = w + c;
    if (dictionary.count(wc)) {
      w = wc;
    } else {
      output.push_back(dictionary[w]);
      dictionary[wc] = next_code++;
      w = string(1, c);
    }
  }

  if (!w.empty()) {
    output.push_back(dictionary[w]);
  }

  cout << output.size() << "\n";
  for (int code : output) {
    cout << code << " ";
  }
  cout << "\n";

  return 0;
}
