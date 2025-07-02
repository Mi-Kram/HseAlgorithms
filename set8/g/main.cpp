#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;
const int MAX_NODES = 1000005;

struct Node {
  int next[ALPHABET_SIZE];
  int link;
  int exit;
  std::vector<int> pattern_ids;

  Node() {
    std::memset(next, -1, sizeof(next));
    link = -1;
    exit = -1;
  }
};

Node trie[MAX_NODES];
int node_count = 1;

int add_pattern(const std::string& pattern, int pattern_id) {
  int current = 0;
  for (char c : pattern) {
    int index = c - 'a';
    if (trie[current].next[index] == -1) {
      trie[node_count] = Node();
      trie[current].next[index] = node_count++;
    }
    current = trie[current].next[index];
  }
  trie[current].pattern_ids.push_back(pattern_id);
  return current;
}

void build_automaton() {
  std::queue<int> q;
  for (int c = 0; c < ALPHABET_SIZE; ++c) {
    if (trie[0].next[c] != -1) {
      trie[trie[0].next[c]].link = 0;
      q.push(trie[0].next[c]);
    } else {
      trie[0].next[c] = 0;
    }
  }

  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int c = 0; c < ALPHABET_SIZE; ++c) {
      int u = trie[v].next[c];
      if (u != -1) {
        int f = trie[v].link;
        while (trie[f].next[c] == -1) f = trie[f].link;
        trie[u].link = trie[f].next[c];

        if (!trie[trie[u].link].pattern_ids.empty()) {
          trie[u].exit = trie[u].link;
        } else {
          trie[u].exit = trie[trie[u].link].exit;
        }

        q.push(u);
      }
    }
  }
}

void process_text(const std::string& text, std::vector<std::vector<int>>& result) {
  int current = 0;
  for (int i = 0; i < (int)text.length(); ++i) {
    int c = text[i] - 'a';
    while (trie[current].next[c] == -1) current = trie[current].link;
    current = trie[current].next[c];

    int temp = current;
    while (temp != -1) {
      for (int id : trie[temp].pattern_ids) {
        result[id].push_back(i + 1);
      }
      temp = trie[temp].exit;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string text;
  std::getline(std::cin, text);

  int n;
  std::cin >> n;
  std::cin.ignore();

  std::vector<std::string> patterns(n);
  std::vector<std::vector<int>> result(n);
  for (int i = 0; i < n; ++i) {
    std::getline(std::cin, patterns[i]);
    add_pattern(patterns[i], i);
  }

  build_automaton();
  process_text(text, result);

  for (int i = 0; i < n; ++i) {
    std::cout << result[i].size();
    for (int pos : result[i]) std::cout << ' ' << pos - patterns[i].length() + 1;
    std::cout << '\n';
  }

  return 0;
}
