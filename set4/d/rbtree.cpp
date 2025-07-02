#include "rbtree.h"
#include <iostream>

void deleteTree(Node *node) {
  if (!node) return;
  deleteTree(node->left);
  deleteTree(node->right);
  delete node;
}

void updateSize(Node *node) {
  node->size = 1;
  if (node->left) node->size += node->left->size;
  if (node->right) node->size += node->right->size;
}

void updateAncestorsSize(Node *node) {
  while (node) {
    updateSize(node);
    node = node->parent;
  }
}

void rotateLeft(Node *node, RBTree *tree) {
  Node *rightChild = node->right;
  node->right = rightChild->left;
  if (rightChild->left) rightChild->left->parent = node;
  rightChild->parent = node->parent;
  if (!node->parent) tree->root = rightChild;
  else if (node == node->parent->left) node->parent->left = rightChild;
  else node->parent->right = rightChild;
  rightChild->left = node;
  node->parent = rightChild;
  updateSize(node);
  updateSize(rightChild);
}

void rotateRight(Node *node, RBTree *tree) {
  Node *leftChild = node->left;
  node->left = leftChild->right;
  if (leftChild->right) leftChild->right->parent = node;
  leftChild->parent = node->parent;
  if (!node->parent) tree->root = leftChild;
  else if (node == node->parent->left) node->parent->left = leftChild;
  else node->parent->right = leftChild;
  leftChild->right = node;
  node->parent = leftChild;
  updateSize(node);
  updateSize(leftChild);
}

void insertFix(Node *node, RBTree *tree) {
  while (node->parent && node->parent->color == Color::RED) {
    Node *grandparent = node->parent->parent;
    if (node->parent == grandparent->left) {
      Node *uncle = grandparent->right;
      if (uncle && uncle->color == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotateLeft(node, tree);
        }
        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateRight(grandparent, tree);
      }
    } else {
      Node *uncle = grandparent->left;
      if (uncle && uncle->color == Color::RED) {
        node->parent->color = Color::BLACK;
        uncle->color = Color::BLACK;
        grandparent->color = Color::RED;
        node = grandparent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotateRight(node, tree);
        }
        node->parent->color = Color::BLACK;
        grandparent->color = Color::RED;
        rotateLeft(grandparent, tree);
      }
    }
    if (node->parent) updateSize(node->parent);
    if (node->parent && node->parent->parent) updateSize(node->parent->parent);
  }
  tree->root->color = Color::BLACK;
  updateSize(tree->root);
}




Node::Node(int key) : key(key), height(0), size(1), left(nullptr), right(nullptr), parent(nullptr), color(Color::RED) {
}

RBTree::RBTree() : root(nullptr) {
}

RBTree::RBTree(std::initializer_list<int> list) : root(nullptr) {
  for (int key : list) insert(key);
}

RBTree::~RBTree() {
  deleteTree(root);
}

void RBTree::insert(int key) {
  if (!root) {
    root = new Node(key);
    root->color = Color::BLACK;
    return;
  }

  Node *current = root, *parent = nullptr;
  while (current) {
    parent = current;
    if (key < current->key) current = current->left;
    else if (key > current->key) current = current->right;
    else return;
  }

  Node* newNode = new Node(key);
  newNode->parent = parent;
  if (key < parent->key) parent->left = newNode;
  else parent->right = newNode;

  updateAncestorsSize(newNode);
  insertFix(newNode, this);
}

int *RBTree::find(int key) {
  Node *current = root;
  while (current) {
    if (key == current->key) return &current->key;
    if (key < current->key) current = current->left;
    else current = current->right;
  }
  return nullptr;
}

int RBTree::size() const {
  return root ? root->size : 0;
}

int *RBTree::lowerBound(int key) {
  Node *current = root;
  Node *result = nullptr;

  while (current) {
    if (current->key < key) {
      current = current->right;
      continue;
    }
    result = current;
    current = current->left;
  }
  return result ? &result->key : nullptr;
}

bool RBTree::empty() const {
  return root == nullptr;
}
