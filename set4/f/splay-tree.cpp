#include "splay-tree.h"

#include <algorithm>


Node::Node(int key, Node *parent) : key(key), left(nullptr), right(nullptr), parent(parent) {
}

SplayTree::SplayTree() : root(nullptr) {
}

SplayTree::~SplayTree() {
  clear(root);
}

void SplayTree::clear(Node *node) {
  if (!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}

void SplayTree::rotateLeft(Node *node) {
  Node *rightChild = node->right;
  if (!rightChild) return;

  node->right = rightChild->left;
  if (rightChild->left) rightChild->left->parent = node;

  rightChild->parent = node->parent;
  if (!node->parent) root = rightChild;
  else if (node == node->parent->left) node->parent->left = rightChild;
  else node->parent->right = rightChild;

  rightChild->left = node;
  node->parent = rightChild;
}

void SplayTree::rotateRight(Node *node) {
  Node *leftChild = node->left;
  if (!leftChild) return;

  node->left = leftChild->right;
  if (leftChild->right) leftChild->right->parent = node;

  leftChild->parent = node->parent;
  if (!node->parent) root = leftChild;
  else if (node == node->parent->left) node->parent->left = leftChild;
  else node->parent->right = leftChild;
  
  leftChild->right = node;
  node->parent = leftChild;
}

int SplayTree::splay(Node *node) {
  if (!node) return 0;

  int rotations = 0;
  while (node->parent) {
    Node *parent = node->parent;
    Node *grandparent = parent->parent;

    if (!grandparent) {
      // Zig rotation
      if (node == parent->left) rotateRight(parent);
      else rotateLeft(parent);
    } else if (node == parent->left && parent == grandparent->left) {
      // Zig-zig (left-left)
      rotateRight(grandparent);
      rotateRight(parent);
      ++rotations;
    } else if (node == parent->right && parent == grandparent->right) {
      // Zig-zig (right-right)
      rotateLeft(grandparent);
      rotateLeft(parent);
      ++rotations;
    } else if (node == parent->right && parent == grandparent->left) {
      // Zig-zag (left-right)
      rotateLeft(parent);
      rotateRight(grandparent);
    } else {
      // Zig-zag (right-left)
      rotateRight(parent);
      rotateLeft(grandparent);
    }

    ++rotations;
  }

  return rotations;
}

void SplayTree::insert(int key) {
  if (!root) {
    root = new Node(key, nullptr);
    return;
  }

  Node *current = root;
  Node *parent = nullptr;

  while (current) {
    parent = current;
    if (key < current->key) current = current->left;
    else if (key > current->key) current = current->right;
    else return;
  }

  Node *newNode = new Node(key, parent);
  if (key < parent->key) parent->left = newNode;
  else parent->right = newNode;
}

Node *SplayTree::find(int key) const {
  Node *current = root;

  while (current) {
    if (key < current->key) current = current->left;
    else if (key > current->key) current = current->right;
    else return current;
  }

  return nullptr;
}

int SplayTree::getHeight() const {
  return root ? getHeight(root) - 1 : 0;
}

int SplayTree::getHeight(Node *node) const {
  if (!node) return 0;
  return 1 + std::max(getHeight(node->left), getHeight(node->right));
}
  