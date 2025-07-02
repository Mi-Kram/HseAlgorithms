#include "avl_tree.h"
#include <algorithm>

Node::Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}
Node::~Node() {}


AVLTree::AVLTree() : root_(nullptr), size_(0) {}
AVLTree::AVLTree(int value) : root_(new Node(value)), size_(1) {}

AVLTree::~AVLTree() {
  while (root_) erase(root_->value);
}



bool AVLTree::empty() {
  return root_ == nullptr;
}

int AVLTree::getSize() {
  return size_;
}

int AVLTree::getHeight() {
  return root_ ? root_->height : 0;
}

int AVLTree::getNodeHeight(Node *node) {
  return node ? node->height : 0;
}

Node *AVLTree::getRoot() {
  return root_;
}



void AVLTree::insert(int value) {
  root_ = insertNode(root_, value);
}

Node *AVLTree::insertNode(Node *node, int value) {
  if (!node) {
    ++size_;
    return new Node(value);
  }

  if (value < node->value) node->left = insertNode(node->left, value);
  else if (value > node->value) node->right = insertNode(node->right, value);
  return balanceNode(node);
}



void AVLTree::erase(int value) {
  root_ = removeNode(root_, value);
}

Node *AVLTree::removeNode(Node *node, int value) {
  if (!node) return nullptr;

  if (value < node->value) node->left = removeNode(node->left, value);
  else if (value > node->value) node->right = removeNode(node->right, value);
  else {
    Node *left = node->left;
    Node *right = node->right;
    delete node;
    --size_;

    if (!right) return left;

    Node *minNode = findMinNode(right);
    minNode->right = removeMinNode(right);
    minNode->left = left;
    return balanceNode(minNode);
  }
  return balanceNode(node);
}

Node *AVLTree::removeMinNode(Node *node) {
  if (!node->left) return node->right;
  node->left = removeMinNode(node->left);
  return balanceNode(node);
}



int *AVLTree::find(int value) {
  Node *node = findNode(root_, value);
  return node ? &node->value : nullptr;
}

Node *AVLTree::findNode(Node *node, int value) {
  if (!node) return nullptr;
  if (value < node->value) return findNode(node->left, value);
  if (value > node->value) return findNode(node->right, value);
  return node;
}

Node *AVLTree::findMinNode(Node *node) {
  return node->left ? findMinNode(node->left) : node;
}






int *AVLTree::traversal() {
  if (size_ == 0) return nullptr;
  int *result = new int[size_];
  int index = 0;
  traversalInternal(root_, result, &index);
  return result;
}

void AVLTree::traversalInternal(Node *node, int *array, int *index) {
  if (!node) return;
  traversalInternal(node->left, array, index);
  array[(*index)++] = node->value;
  traversalInternal(node->right, array, index);
}



int *AVLTree::lowerBound(int value) {
  Node *node = lowerBoundInternal(root_, value);
  return node ? &node->value : nullptr;
}

Node *AVLTree::lowerBoundInternal(Node *current, int value) const {
  if (!current) return nullptr;
  if (current->value >= value) {
    Node *candidate = lowerBoundInternal(current->left, value);
    return candidate ? candidate : current;
  }
  return lowerBoundInternal(current->right, value);
}


int AVLTree::balanceFactor(Node *node) {
  return node ? getNodeHeight(node->left) - getNodeHeight(node->right) : 0;
}

void AVLTree::balanceHeight(Node *node) {
  if (!node) return;
  node->height = 1 + std::max(getNodeHeight(node->left), getNodeHeight(node->right));
}

Node *AVLTree::rotateRight(Node *node) {
  Node* left = node->left;
  Node* right = left->right;

  left->right = node;
  node->left = right;

  balanceHeight(node);
  balanceHeight(left);

  return left;
}

Node *AVLTree::rotateLeft(Node *node) {
  Node* right = node->right;
  Node* left = right->left;

  right->left = node;
  node->right = left;

  balanceHeight(node);
  balanceHeight(right);

  return right;
}

Node *AVLTree::balanceNode(Node *node) {
  balanceHeight(node);
  int bf = balanceFactor(node);

  if (bf > 1) {
    if (balanceFactor(node->left) < 0) node->left = rotateLeft(node->left);
    return rotateRight(node);
  }

  if (bf < -1) {
    if (balanceFactor(node->right) > 0) node->right = rotateRight(node->right);
    return rotateLeft(node);
  }

  return node;
}


