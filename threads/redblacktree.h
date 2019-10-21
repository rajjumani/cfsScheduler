#include "thread.h"

#ifndef RedBlackTree_H
#define RedBlackTree_H

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

class RedBlackTree
{
private:
    Node *root;

protected:
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    void insertBalanceTree(Node *&);
    void deleteBalanceTree(Node *&);
    void inorderBST(Node *&);
    Node *minValueNode(Node *&);
    Node *insertBST(Node *&, Node *&);
    Node *deleteBST(Node *&, Node *&, int);

public:
    RedBlackTree();
    void insertValue(int, Thread *&);
    void deleteValue(int, Node *&);
    void inorder();
    void changeNodeColor(Node *&ptr, string pos);
    Node *getRoot();
    void manageBST(Node *&root, bool leftFlag, Node *&ptr);
    void getLeftChild(Node *&left_child, Node *&ptr);
    void getRightChild(Node *&right_child, Node *&ptr);
    void deleteNode(Node *&node, Node *&child);
    void setSibParColor(Node *&sibling, Node *&parent);
    void setParentColor(Node *&parent);
    void setSiblingColor(Node *&sibling, Node *&parent);
    void setSiblingColor1(Node *&sibling, Node *&parent);
    void RLRotate(Node *&ptr, Node *&parent, Node *&grandparent);
    void LRRotate(Node *&ptr, Node *&parent, Node *&grandparent);
    void checkRotateRight(Node *&ptr, Node *&parent);
    void checkRotateLeft(Node *&ptr, Node *&parent);
};

#endif
