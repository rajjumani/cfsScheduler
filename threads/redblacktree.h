//
// Red Black Tree Definition
//
#include "thread.h"

#ifndef RED_BLACK_TREE_RBTREE_H
#define RED_BLACK_TREE_RBTREE_H

enum Color
{
    RED,
    BLACK,
    DOUBLE_BLACK
};

class Node
{
public:
    int data;
    int color;
    Thread *reqThread;
    Node *left, *right, *parent;
    int getColor();
    void setColor(int);
    explicit Node(int);
};

class RBTree
{
private:
    Node *root;

protected:
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void fixInsertRBTree(Node *&);
    void fixDeleteRBTree(Node *&);
    void inorderBST(Node *&);
    void preorderBST(Node *&);
    Node *minValueNode(Node *&);
    Node *insertBST(Node *&, Node *&);
    Node *deleteBST(Node *&, Node *&, int);

public:
    RBTree();
    void insertValue(int, Thread *&);
    void deleteValue(int, Node *&);
    void merge(RBTree);
    void inorder();
    void preorder();
    void changeNodeColor(Node *&ptr, string pos);
    Node *getRoot();
    void printTree();
    void searchBST(string searchSide, Node *&root, Node *&ptr);
    void rotate(string rotateNode, Node *&ptr, Node *&child, bool rotateFlag);
    void manageBST(Node *&root, bool leftFlag, Node *&ptr);
    void getLeftChild(Node *&left_child, Node *&ptr);
    void getRightChild(Node *&right_child, Node *&ptr);
};

#endif //RED_BLACK_TREE_RBTREE_H
