#ifndef AVL_H_
#define AVL_H_

#include <string>

struct AVLNode{
  int32_t val;
  AVLNode *left;
  AVLNode *right;
  int32_t height;

AVLNode():val(0), left(NULL), right(NULL), height(0) {}
AVLNode(int32_t val, AVLNode *l, AVLNode *r): val(val), left(l), right(r), height(0) {}
};

class AVLTree
{
public:
  AVLTree ();
  virtual ~AVLTree ();
  void Insert (int32_t val);
  // choose smallest node on the right subtree when deleting a node with two children
  void Delete (int32_t val);
  bool Access (int32_t val);
  std::string PrintPreOrder () const;
  std::string PrintInOrder () const;

private:
  /* data */
  AVLNode* root;
  void destroy(AVLNode* &tree);
  int32_t height(AVLNode* tree);
  int32_t max(int32_t a, int32_t b);
  AVLNode* Insert(int32_t val, AVLNode* &tree);
  AVLNode* Delete(int32_t val, AVLNode* &tree);
  bool Access(int32_t val, AVLNode* &tree);
  AVLNode* minimum(AVLNode* &tree);
  AVLNode* maximum(AVLNode* &tree);
  AVLNode* lLRotation(AVLNode* &tree);
  AVLNode* rRRotation(AVLNode* &tree);
  AVLNode* lRRotation(AVLNode* &tree);
  AVLNode* rLRotation(AVLNode* &tree);
  std::string preOrder(AVLNode* tree) const;
  std::string inOrder(AVLNode* tree) const;
};

#endif /* end of include guard: AVL_H_ */
