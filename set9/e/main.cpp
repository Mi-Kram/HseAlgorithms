#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
  char ch;
  int freq;
  Node* left;
  Node* right;

  Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {
  }
  Node(Node* l, Node* r) : ch(0), freq(l->freq + r->freq), left(l), right(r) {
  }
};

struct Compare {
  bool operator()(Node* a, Node* b) {
    return b->freq < a->freq;
  }
};

void generateCodes(Node* node, const string& prefix, unordered_map<char, string>& codes) {
  if (!node) return;

  if (!node->left && !node->right) {
    codes[node->ch] = prefix.empty() ? "0" : prefix;  // для случая одного символа
  }

  generateCodes(node->left, prefix + "0", codes);
  generateCodes(node->right, prefix + "1", codes);
}

void freeTree(Node* node) {
  if (!node) return;
  freeTree(node->left);
  freeTree(node->right);
  delete node;
}

int main() {
  string s;
  cin >> s;

  unordered_map<char, int> freq;
  for (char ch : s) {
    ++freq[ch];
  }

  priority_queue<Node*, vector<Node*>, Compare> heap;
  for (const auto& [ch, fr] : freq) {
    heap.push(new Node(ch, fr));
  }

  while (heap.size() > 1) {
    Node* a = heap.top();
    heap.pop();
    Node* b = heap.top();
    heap.pop();
    heap.push(new Node(a, b));
  }

  Node* root = heap.top();
  unordered_map<char, string> codes;
  generateCodes(root, "", codes);

  string encoded;
  for (char ch : s) {
    encoded += codes[ch];
  }

  cout << codes.size() << " " << encoded.size() << "\n";
  for (const auto& [ch, code] : codes) {
    cout << ch << ": " << code << "\n";
  }
  cout << encoded << "\n";

  freeTree(root);
  return 0;
}
