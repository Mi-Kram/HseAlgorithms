#include <iostream>

struct Node {
  int key;
  bool is_red;
  Node *left, *right;

  Node(int key, bool is_red = false) : key(key), is_red(is_red), left(nullptr), right(nullptr) { }
};

void clear(Node* node);
Node* read_tree(size_t n, size_t root_number);
bool is_black_red(Node* root);
bool check_red(Node* node);
bool check_black(Node* node, int current_black_height, int& black_height);
int path(Node* node);
bool check_value(Node* node);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  size_t n, root_number;
  std::cin >> n;

  if (!n) {
    std::cout << "NO";
    return 0;
  }
  
  std::cin >> root_number;
  Node* root = read_tree(n, root_number);
  std::cout << (is_black_red(root) ? "YES" : "NO") << '\n';

  clear(root);
  return 0;
}

void clear(Node* node) {
  if (!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

Node* read_tree(size_t n, size_t root_number) {
  Node** arr = new Node*[n]{};
  size_t number;
  int key;
  std::string left, right;
  char color;

  for (size_t i = 0; i < n; i++) {
    std::cin >> number >> key >> left >> right >> color;
    if (arr[number-1]) {
      arr[number-1]->key = key;
      arr[number-1]->is_red = color == 'R';
    }
    else arr[number-1] = new Node(key, color == 'R');
    
    if (left != "null") {
      int l = std::stoi(left) - 1;
      if (arr[l]) arr[number-1]->left = arr[l];
      else arr[number-1]->left = arr[l] = new Node(-1);
    }
    
    if (right != "null") {
      int r = std::stoi(right) - 1;
      if (arr[r]) arr[number-1]->right = arr[r];
      else arr[number-1]->right = arr[r] = new Node(-1);
    }
  }

  Node* root = arr[root_number - 1];
  delete[] arr;
  return root;
}

bool is_black_red(Node* root) {
  if (!root || root->is_red) return false;
  int tmp = -1;
  return check_red(root) && check_black(root, 0, tmp) && check_value(root);
}

bool check_red(Node* node) {
  if (!node) return true;

  if (node->is_red && ((node->left && node->left->is_red) || (node->right && node->right->is_red)))
    return false;
  return check_red(node->left) && check_red(node->right);
}

bool check_black(Node* node, int current_black_height, int& black_height) {
  if (!node) {
    if (black_height == -1) black_height = current_black_height;
    return black_height == current_black_height;
  }

  if (!node->is_red) ++current_black_height;

  return check_black(node->left, current_black_height, black_height) &&
          check_black(node->right, current_black_height, black_height);
}

int path(Node* node) {
  if (!node) return 0;
  return std::min(path(node->left), path(node->right)) + 1;
}

bool check_value(Node* node) {
  if (!node) return true;
  if (node->left && node->key <= node->left->key) return false;
  if (node->right && node->right->key <= node->key) return false;
  return check_value(node->left) && check_value(node->right);
}
