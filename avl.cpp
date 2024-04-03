#include <algorithm>
#include <iomanip>
#include <iostream>

template <typename T> class AVLNode {
public:
  T data;
  AVLNode *left, *right;
  int height;

  AVLNode(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
};

template <typename T> class AVLTree {
private:
  AVLNode<T> *root;

  AVLNode<T> *insert(AVLNode<T> *node, T data) {
    if (!node)
      return new AVLNode<T>(data);

    if (data < node->data)
      node->left = insert(node->left, data);
    else if (data > node->data)
      node->right = insert(node->right, data);
    else
      return node;

    updateHeight(node);
    return balance(node);
  }

  AVLNode<T> *minValueNode(AVLNode<T> *node) {
    AVLNode<T> *current = node;
    while (current && current->left != nullptr)
      current = current->left;
    return current;
  }

  AVLNode<T> *deleteNode(AVLNode<T> *root, T data) {
    if (!root)
      return root;

    if (data < root->data)
      root->left = deleteNode(root->left, data);
    else if (data > root->data)
      root->right = deleteNode(root->right, data);
    else {
      if ((root->left == nullptr) || (root->right == nullptr)) {
        AVLNode<T> *temp = root->left ? root->left : root->right;
        if (temp == nullptr) {
          temp = root;
          root = nullptr;
        } else
          *root = *temp;
        delete temp;
      } else {
        AVLNode<T> *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
      }
    }

    if (!root)
      return root;

    updateHeight(root);
    return balance(root);
  }

  void updateHeight(AVLNode<T> *&node) {
    node->height = 1 + std::max(height(node->left), height(node->right));
  }

  int getBalanceFactor(AVLNode<T> *node) {
    if (!node)
      return 0;
    return height(node->left) - height(node->right);
  }

  AVLNode<T> *balance(AVLNode<T> *node) {
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1) {
      if (getBalanceFactor(node->left) < 0)
        node->left = rotateLeft(node->left);
      return rotateRight(node);
    }
    if (balanceFactor < -1) {
      if (getBalanceFactor(node->right) > 0)
        node->right = rotateRight(node->right);
      return rotateLeft(node);
    }
    return node;
  }

  AVLNode<T> *rotateRight(AVLNode<T> *y) {
    AVLNode<T> *x = y->left;
    AVLNode<T> *T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
  }

  AVLNode<T> *rotateLeft(AVLNode<T> *x) {
    AVLNode<T> *y = x->right;
    AVLNode<T> *T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
  }

  int height(AVLNode<T> *node) { return node ? node->height : 0; }

  void inOrder(AVLNode<T> *root) {
    if (root != nullptr) {
      inOrder(root->left);
      std::cout << root->data << " ";
      inOrder(root->right);
    }
  }

  AVLNode<T> *search(AVLNode<T> *root, T data) {
    if (root == nullptr || root->data == data)
      return root;

    if (root->data < data)
      return search(root->right, data);

    return search(root->left, data);
  }

public:
  AVLTree() : root(nullptr) {}

  void insert(T data) { root = insert(root, data); }

  void deleteData(T data) { root = deleteNode(root, data); }

  void inOrder() {
    inOrder(root);
    std::cout << std::endl;
  }

  void searchData(T data) {
    AVLNode<T> *node = search(root, data);
    if (node != nullptr) {
      std::cout << "Data: " << node->data << " Height: " << node->height;
      if (node != root) {
        AVLNode<T> *parent = searchParent(root, node);
        std::cout << " Parent Data: " << (parent ? parent->data : T());
      }
      std::cout << std::endl;
    } else {
      std::cout << "Data not found" << std::endl;
    }
  }

private:
  AVLNode<T> *searchParent(AVLNode<T> *root, AVLNode<T> *child) {
    if (root == nullptr || root->left == child || root->right == child) {
      return nullptr;
    }

    if (root->data > child->data)
      return searchParent(root->left, child);
    else
      return searchParent(root->right, child);
  }
};

int main() {
  AVLTree<std::string> stringTree;
  AVLTree<int> intTree;
  AVLTree<double> doubleTree;

  stringTree.insert("Milton");
  stringTree.insert("Ajax");
  stringTree.insert("Clarington");
  stringTree.insert("Brock");
  stringTree.insert("Oshawa");
  stringTree.insert("Pickering");
  stringTree.insert("Uxbridge");
  stringTree.insert("Whitby");
  stringTree.insert("Burlington");
  stringTree.insert("Oakville");
  stringTree.insert("Brampton");
  stringTree.insert("Caledon");
  stringTree.insert("Mississauga");
  stringTree.insert("Aurora");
  stringTree.insert("Georgina");

  intTree.insert(95);
  intTree.insert(301);
  intTree.insert(501);
  intTree.insert(801);
  intTree.insert(90);
  intTree.insert(70);
  intTree.insert(80);
  intTree.insert(25);
  intTree.insert(67);
  intTree.insert(89);
  intTree.insert(11);

  doubleTree.insert(84.8);
  doubleTree.insert(103.5);
  doubleTree.insert(67.8);
  doubleTree.insert(90.3);
  doubleTree.insert(23.5);
  doubleTree.insert(67.1);
  doubleTree.insert(44.5);
  doubleTree.insert(89.2);
  doubleTree.insert(100.5);
  doubleTree.insert(300.2);

  std::cout << "String Tree Before Inserting 'Stouffville':\n";
  stringTree.inOrder();
  stringTree.insert("Stouffville");
  std::cout << "String Tree After Inserting 'Stouffville':\n";
  stringTree.inOrder();

  std::cout << "\nInteger Tree Before Inserting 506:\n";
  intTree.inOrder();
  intTree.insert(506);
  std::cout << "Integer Tree After Inserting 506:\n";
  intTree.inOrder();

  std::cout << "\nDouble Tree Before Inserting 88.5:\n";
  doubleTree.inOrder();
  doubleTree.insert(88.5);
  std::cout << "Double Tree After Inserting 88.5:\n";
  doubleTree.inOrder();

  std::cout << "\nString Tree Before Deleting 'Caledon':\n";
  stringTree.inOrder();
  stringTree.deleteData("Caledon");
  std::cout << "String Tree After Deleting 'Caledon':\n";
  stringTree.inOrder();

  std::cout << "\nInteger Tree Before Deleting 89:\n";
  intTree.inOrder();
  intTree.deleteData(89);
  std::cout << "Integer Tree After Deleting 89:\n";
  intTree.inOrder();

  std::cout << "\nDouble Tree Before Deleting 23.5:\n";
  doubleTree.inOrder();
  doubleTree.deleteData(23.5);
  std::cout << "Double Tree After Deleting 23.5:\n";
  doubleTree.inOrder();

  std::cout << "\nSearching for 'Whitby' in String Tree:\n";
  stringTree.searchData("Whitby");

  std::cout << "\nSearching for 11 in Integer Tree:\n";
  intTree.searchData(11);

  std::cout << "\nSearching for 90.3 in Double Tree:\n";
  doubleTree.searchData(90.3);

  return 0;
}
