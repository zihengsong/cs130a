#include <iostream>
#include <sstream>
#include "avl.h"
using namespace std;

// Public Methods

AVLTree::AVLTree():root(NULL){}

AVLTree::~AVLTree(){
  destroy(root);
}

void AVLTree::Insert(int32_t val){
  Insert(val, root);
}

void AVLTree::Delete(int32_t val){
  Delete(val, root);
}

bool AVLTree::Access(int32_t val){
  return Access(val, root);
}

std::string AVLTree::PrintPreOrder () const{
  std::string s = preOrder(root);
  s.pop_back();
  return s;
}

std::string AVLTree::PrintInOrder () const{
  std::string s = inOrder(root);
  s.pop_back();
  return s;
}

// Private Methods

void AVLTree::destroy(AVLNode* &tree){
  if (tree == NULL)
    return;
  if (tree->left != NULL)
    destroy(tree->left);
  if (tree->right != NULL)
    destroy(tree->right);
  delete tree;
}

int32_t AVLTree::height(AVLNode* tree){
  if (tree != NULL)
    return tree->height;
  return 0;
}

int32_t AVLTree::max(int32_t a, int32_t b){
  return a > b ? a : b;
}

AVLNode* AVLTree::Insert(int32_t val, AVLNode* &tree){
  if (tree == NULL){
    tree = new AVLNode(val, NULL, NULL);
    //cout << "test1 " << val << " inorder " << PrintInOrder() << endl;
  }
  else if (val < tree->val){
    tree->left = Insert(val, tree->left);
    //cout << "test2 " << val << " inorder " << PrintInOrder() << endl;
    if (height(tree->left) - height(tree->right) == 2){
      if (val < tree->left->val)
        tree = lLRotation(tree);
      else
        tree = lRRotation(tree);
    }
  }
  else if (val > tree->val){
    tree->right = Insert(val, tree->right);
    if (height(tree->right) - height(tree->left) == 2){
      if (val > tree->right->val)
        tree = rRRotation(tree);
      else
        tree = rLRotation(tree);
    }
  }
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  return tree;
}

AVLNode* AVLTree::Delete(int32_t val, AVLNode* &tree){
  if (tree == NULL)
    return tree;
  else if (val > tree->val)
    tree->right = Delete(val, tree->right);
  else if (val < tree->val)
    //cout << " test 1 " << tree->val << " " << tree->left->val << endl;
    tree->left = Delete(val, tree->left);
  if (val == tree->val){
    //cout << " test 2 " << tree->val << endl;
    if (tree->left != NULL && tree->right != NULL){
      //cout << " test 3 " << endl;
      AVLNode* min = minimum(tree->right);
      tree->val = min->val;
      //cout << " test 4 " << tree->val << endl;
      tree->right = Delete(min->val, tree->right);
      //cout << " test 5 " << endl;
    }
    else{
      AVLNode* tmp = tree;
      tree = (tree->left != NULL) ? tree->left : tree->right;
      delete tmp;
      /*      if (tree->left != NULL){
        AVLNode* tmp = tree->left;
	tree->val = tree->left->val;
        delete tmp;
      }
      else if (tree->right != NULL){
        AVLNode* tmp = tree->right;
	tree->val = tree->right->val;
	delete tmp;
        //cout << " test 6 " << tree->val << endl;
        //delete tmp;
        //cout << " test 7 " << endl;
      }
      else{
        AVLNode* tmp = tree;
        delete tmp;
        //cout << " test 7 " << endl;
	}*/
    }
  }
  if (tree != NULL){
    if (height(tree->left) - height(tree->right) == 2){
      if (height(tree->left->right) > height(tree->left->left))
        tree = lRRotation(tree);
      else
        tree = lLRotation(tree);
    }
    if (height(tree->right) - height(tree->left) == 2){
      if (height(tree->right->left) > height(tree->right->right))
        tree = rLRotation(tree);
      else
        tree = rRRotation(tree);
    }
  }
  //cout << " test end " << tree->val << " " << PrintInOrder() << endl;
  return tree;
}

bool AVLTree::Access(int32_t val, AVLNode* &tree){
  if(tree == NULL)
    return false;
  else if(val == tree->val)
    return true;
  else if(val < tree->val)
    return Access(val, tree->left);
  else
    return Access(val, tree->right);
}

AVLNode* AVLTree::minimum(AVLNode* &tree){
  if (tree != NULL){
    while (tree->left != NULL)
      tree = tree->left;
    return tree;
  }
  return NULL;
}

AVLNode* AVLTree::maximum(AVLNode* &tree){
  if (tree != NULL){
    while (tree->right != NULL)
      tree = tree->right;
    return tree;
  }
  return NULL;
}

AVLNode* AVLTree::lLRotation(AVLNode* &tree){
  AVLNode* temp = tree->left;
  tree->left = temp->right;
  temp->right = tree;
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  temp->height = max(height(temp->left), height(temp->right)) + 1;
  return temp;
}

AVLNode* AVLTree::rRRotation(AVLNode* &tree){
  AVLNode* temp = tree->right;
  tree->right = temp->left;
  temp->left = tree;
  tree->height = max(height(tree->left), height(tree->right)) + 1;
  temp->height = max(height(temp->left), height(temp->right)) + 1;
  return temp;
}

AVLNode* AVLTree::lRRotation(AVLNode* &tree){
  tree->left = rRRotation(tree->left);
  return lLRotation(tree);
}

AVLNode* AVLTree::rLRotation(AVLNode* &tree){
  tree->right = lLRotation(tree->right);
  return rRRotation(tree);
}

std::string AVLTree::preOrder(AVLNode* tree) const{
  if (tree == NULL)
    return "";
  else{
    std::string order = "";
    order += std::to_string(tree->val);
    order += " ";
    order += preOrder(tree->left);
    order += preOrder(tree->right);
    return order;
  }
}

std::string AVLTree::inOrder(AVLNode* tree) const{
  if (tree == NULL)
    return "";
  else{
    std::string order = "";
    order += inOrder(tree->left);
    order += std::to_string(tree->val);
    order += " ";
    order += inOrder(tree->right);
    return order;
  }
}
