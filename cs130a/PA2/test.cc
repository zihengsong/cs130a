#include <iostream>

#include "gtest/gtest.h"

#include "avl.h"
#include "bst.h"

using namespace std;

AVLTree avltree;
BinarySearchTree bst;
int arr[50000];

TEST (AVLTree, Test1) {
  for (int i = 1; i <= 50000; i++)
    avltree.Insert(i);
}

TEST (AVLTree, Test2) {
  for (int i = 1; i <= 50000; i++)
    avltree.Access(i);
}

TEST (AVLTree, Test3) {
  for (int i = 1; i <= 50000; i++)
    avltree.Delete(i);
}

TEST (AVLTree, Test4) {
  for (int i = 1; i <= 50000; i++)
    avltree.Insert(i);
}

TEST (AVLTree, Test5) {
  for (int i = 50000; i >= 1; i--)
    avltree.Access(i);
}

TEST (AVLTree, Test6) {
  for (int i = 50000; i >= 1; i--)
    avltree.Delete(i);
}

TEST (AVLTree, Test7) {
  for (int i = 0; i < 50000; i++)
    avltree.Insert(arr[i]);
}

TEST (AVLTree, Test8) {
  for (int i = 0; i < 50000; i++)
    avltree.Access(arr[i]);
}

TEST (AVLTree, Test9) {
  // cout << avltree.PrintInOrder() << endl;
  for (int i = 0; i < 50000; i++)
    avltree.Delete(arr[i]);
  //cout << avltree.PrintInOrder() << endl;
}

TEST (BinarySearchTree, Test10) {
  for (int i = 1; i <= 50000; i++)
    bst.Insert(i);
}

TEST (BinarySearchTree, Test11) {
  for (int i = 1; i <= 50000; i++)
    bst.Access(i);
}

TEST (BinarySearchTree, Test12) {
  for (int i = 1; i <= 50000; i++)
    bst.Delete(i);
}

TEST (BinarySearchTree, Test13) {
  for (int i = 1; i <= 50000; i++)
    bst.Insert(i);
}

TEST (BinarySearchTree, Test14) {
  for (int i = 50000; i >= 1; i--)
    bst.Access(i);
}

TEST (BinarySearchTree, Test15) {
  for (int i = 50000; i >= 1; i--)
    bst.Delete(i);
}

TEST (BinarySearchTree, Test16) {
  for (int i = 0; i < 50000; i++)
    bst.Insert(arr[i]);
}

TEST (BinarySearchTree, Test17) {
  for (int i = 0; i < 50000; i++)
    bst.Access(arr[i]);
}

TEST (BinarySearchTree, Test18) {
  for (int i = 0; i < 50000; i++)
    bst.Delete(arr[i]);
}

int main(int argc, char *argv[])
{
  // int arr[50000];
  for (int i = 0; i < 50000; i++){
    arr[i] = i + 1;
  }
  random_shuffle(begin(arr), end(arr));
  //  for (int i = 0; i < 50000; i++)
  // cout << arr[i] << " ";
  ::testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}
