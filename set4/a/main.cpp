#include <algorithm>
#include <iostream>

struct TreeNode {
  int value;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int val) : value(val), left(nullptr), right(nullptr) {
  }
};

class BinaryTree {
 public:
  TreeNode* root;

  BinaryTree();
  ~BinaryTree();

  void insert(int value);
  bool isAVL();

 private:
  TreeNode* insertNode(TreeNode* node, int value);
  int checkAVL(TreeNode* node);
  void clear(TreeNode* node);
};

int main() {
  BinaryTree tree;
  int value;

  while (std::cin >> value && value)
    tree.insert(value);

  std::cout << (tree.isAVL() ? "YES" : "NO");
  return 0;
}

BinaryTree::BinaryTree() : root(nullptr) { }
BinaryTree::~BinaryTree() {
  clear(root);
}

void BinaryTree::insert(int value) {
  root = insertNode(root, value);
}

bool BinaryTree::isAVL() {
  return checkAVL(root) != -1;
}

TreeNode* BinaryTree::insertNode(TreeNode* node, int value) {
  if (!node)                    return new TreeNode(value);
  if (value < node->value)      node->left = insertNode(node->left, value);
  else if (value > node->value) node->right = insertNode(node->right, value);
  return node;
}

int BinaryTree::checkAVL(TreeNode* node) {
  if (!node) return 0;

  int leftHeight  = checkAVL(node->left);
  int rightHeight = checkAVL(node->right);

  if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) return -1;
  return std::max(leftHeight, rightHeight) + 1;
}

void BinaryTree::clear(TreeNode* node) {
  if (!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}