#include <bits/stdc++.h>
#include "redblacktree.h"

Node::Node(int data)
{
    left = NULL;
    right = NULL;
    parent = NULL;
    color = RED;
    this->data = data;
}

RedBlackTree::RedBlackTree()
{
    root = NULL;
}

// return color of node
int Node::getColor()
{
    if (this != NULL)
        return this->color;

    return BLACK;
}

//sets color of node
void Node::setColor(int color)
{
    if (this != NULL)
        this->color = color;
}

// manipulates the BST after insertion
void RedBlackTree::manageBST(Node *&root, bool leftFlag, Node *&ptr)
{
    if (leftFlag)
    {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    else
    {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
}

// return the root of tree
Node *RedBlackTree::getRoot()
{
    return root;
}

// rotates node to left
void RedBlackTree::rotateLeft(Node *&ptr)
{
    Node *right_child = ptr->right;

    getRightChild(right_child, ptr);
    right_child->left = ptr;
    ptr->parent = right_child;
}

// get the left child of node
void RedBlackTree::getLeftChild(Node *&left_child, Node *&ptr)
{
    bool leftFlag = true;
    Node *ptrParent = ptr->parent;
    ptr->left = left_child->right;

    if (ptr->left != NULL && leftFlag)
    {
        ptr->left->parent = ptr;
    }

    left_child->parent = ptrParent;
    if (ptrParent == NULL)
        root = left_child;
    else if (ptr != ptrParent->left)
        ptrParent->right = left_child;
    else
        ptrParent->left = left_child;
}

// get the right child of node
void RedBlackTree::getRightChild(Node *&right_child, Node *&ptr)
{
    bool rightFlag = true;
    Node *ptrParent = ptr->parent;
    ptr->right = right_child->left;

    if (ptr->right != NULL && rightFlag)
        ptr->right->parent = ptr;

    right_child->parent = ptrParent;
    if (ptrParent == NULL)
        root = right_child;
    else if (ptr != ptrParent->left)
        ptrParent->right = right_child;
    else
        ptrParent->left = right_child;
}

// rotate the tree to right around the node
void RedBlackTree::rotateRight(Node *&ptr)
{
    Node *left_child = ptr->left;

    getLeftChild(left_child, ptr);
    left_child->right = ptr;
    ptr->parent = left_child;
}

// check if it can rotate left
void RedBlackTree::checkRotateLeft(Node *&ptr, Node *&parent)
{
    rotateLeft(parent);
    ptr = parent;
    parent = ptr->parent;
}

// check if it can rotate right
void RedBlackTree::checkRotateRight(Node *&ptr, Node *&parent)
{
    rotateRight(parent);
    ptr = parent;
    parent = ptr->parent;
}

// rotate from right to left
void RedBlackTree::RLRotate(Node *&ptr, Node *&parent, Node *&grandparent)
{
    rotateLeft(grandparent);
    swap(parent->color, grandparent->color);
    ptr = parent;
}

// rotate from left to right
void RedBlackTree::LRRotate(Node *&ptr, Node *&parent, Node *&grandparent)
{

    rotateRight(grandparent);
    swap(parent->color, grandparent->color);
    ptr = parent;
}

// inserts node recursively according to BST
Node *RedBlackTree::insertBST(Node *&root, Node *&ptr)
{
    if (root == NULL)
        return ptr;

    if (ptr->data <= root->data)
    {
        manageBST(root, true, ptr);
    }
    else if (ptr->data > root->data)
    {
        manageBST(root, false, ptr);
    }
    return root;
}

// adjusts node color of nodes
void RedBlackTree::changeNodeColor(Node *&ptr, string pos)
{
    bool leftFlag = true;
    Node *parent = ptr->parent;
    Node *grandparent = parent->parent;
    Node *uncle;
    if (pos == "left")
        uncle = grandparent->right;
    else
        uncle = grandparent->left;

    if (uncle->getColor() == RED)
    {
        uncle->setColor(BLACK);
        parent->setColor(BLACK);
        grandparent->setColor(RED);
        ptr = grandparent;
    }
    else
    {
        if (pos == "left" && leftFlag)
        {
            if (ptr == parent->right)
            {
                checkRotateLeft(ptr, parent);
            }
            LRRotate(ptr, parent, grandparent);
        }
        else if (leftFlag)
        {
            if (ptr == parent->left)
            {
                checkRotateRight(ptr, parent);
            }
            RLRotate(ptr, parent, grandparent);
        }
    }
}

// delete the node from tree
void RedBlackTree::deleteNode(Node *&node, Node *&child)
{
    if (node == node->parent->left)
    {
        node->parent->left = child;
        if (child != NULL)
            child->parent = node->parent;
        child->setColor(BLACK);
        delete (node);
    }
    else
    {
        node->parent->right = child;
        if (child != NULL)
            child->parent = node->parent;
        child->setColor(BLACK);
        delete (node);
    }
}

// insert the node to tree
void RedBlackTree::insertValue(int n, Thread *&reqThread)
{
    Node *node = new Node(n);
    node->reqThread = reqThread;
    root = insertBST(root, node);
    insertBalanceTree(node);
}

// balance the tree after insertion
void RedBlackTree::insertBalanceTree(Node *&ptr)
{
    Node *parent = NULL;
    Node *grandparent = NULL;
    while (ptr != root && ptr->getColor() == RED && ptr->parent->getColor() == RED)
    {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left)
            changeNodeColor(ptr, "left");
        else
            changeNodeColor(ptr, "right");
    }
    root->setColor(BLACK);
}

// set sibling color
void RedBlackTree::setSiblingColor1(Node *&sibling, Node *&parent)
{
    sibling->right->setColor(BLACK);
    sibling->setColor(RED);
    rotateLeft(sibling);
    sibling = parent->left;
}

// adjust sibling color before right rotatation
void RedBlackTree::setSiblingColor(Node *&sibling, Node *&parent)
{
    sibling->setColor(parent->color);
    parent->setColor(BLACK);
    sibling->left->setColor(BLACK);
    rotateRight(parent);
}

// set parent node color
void RedBlackTree::setParentColor(Node *&parent)
{
    if (parent->getColor() == RED)
        parent->setColor(BLACK);
    else
        parent->setColor(DOUBLE_BLACK);
}

// set Sibling Parent color
void RedBlackTree::setSibParColor(Node *&sibling, Node *&parent)
{
    sibling->setColor(BLACK);
    parent->setColor(RED);
    rotateLeft(parent);
}

// Balance tree after deletion of node
void RedBlackTree::deleteBalanceTree(Node *&node)
{
    if (node == NULL)
        return;

    if (node == root && root != NULL)
    {
        if (root->left == NULL && root->right == NULL)
        {
            root = NULL;
            return;
        }
        else if (root->right != NULL)
        {
            root = root->right;
            root->parent = NULL;
            root->setColor(BLACK);
            return;
        }
        return;
    }

    if (node->getColor() == RED || node->left->getColor() == RED || node->right->getColor() == RED)
    {
        Node *child = node->left != NULL ? node->left : node->right;

        deleteNode(node, child);
    }
    else
    {
        Node *sibling = NULL;
        Node *parent = NULL;
        Node *ptr = node;
        ptr->setColor(DOUBLE_BLACK);
        while (ptr != root && ptr->getColor() == DOUBLE_BLACK)
        {
            parent = ptr->parent;
            if (ptr == parent->left)
            {
                sibling = parent->right;
                if (sibling->getColor() == RED)
                {
                    setSibParColor(sibling, parent);
                }
                else
                {
                    if (sibling->left->getColor() == BLACK && sibling->right->getColor() == BLACK)
                    {
                        sibling->setColor(RED);
                        setParentColor(parent);
                        ptr = parent;
                    }
                    else
                    {
                        if (sibling->right->getColor() == BLACK)
                        {
                            sibling->left->setColor(BLACK);
                            sibling->setColor(RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        sibling->setColor(parent->color);
                        parent->setColor(BLACK);
                        sibling->right->setColor(BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            }
            else
            {
                sibling = parent->left;
                if (sibling->getColor() == RED)
                {
                    sibling->setColor(BLACK);
                    parent->setColor(RED);
                    rotateRight(parent);
                }
                else
                {
                    if (sibling->left->getColor() == BLACK && sibling->right->getColor() == BLACK)
                    {
                        sibling->setColor(RED);
                        setParentColor(parent);
                        ptr = parent;
                    }
                    else
                    {
                        if (sibling->left->getColor() == BLACK)
                        {
                            setSiblingColor1(sibling, parent);
                        }
                        setSiblingColor(sibling, parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        delete (node);
        root->setColor(BLACK);
    }
}

// finds the minimum value node
Node *RedBlackTree::minValueNode(Node *&node)
{

    Node *ptr = node;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}

// recursively traverse tree to delete node
Node *RedBlackTree::deleteBST(Node *&root, Node *&dNode, int data)
{
    if (root == NULL)
        return root;

    if (data <= root->data)
    {
        if (root == dNode)
            return root;
        else
            return deleteBST(root->left, dNode, data);
    }

    if (data > root->data)
        return deleteBST(root->right, dNode, data);

    if (root->left == NULL || root->right == NULL)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, dNode, temp->data);
}

// delete the value from tree
void RedBlackTree::deleteValue(int data, Node *&ptr)
{
    Node *node = deleteBST(root, ptr, data);
    deleteBalanceTree(node);
}

// recursively call this function to get inorder of tree
void RedBlackTree::inorderBST(Node *&ptr)
{
    if (ptr == NULL)
        return;

    inorderBST(ptr->left);
    string node_color;
    if (ptr->color == 0)
        node_color = "RED";
    else
        node_color = "BLACK";
    cout << ptr->reqThread->getName() << " | " << ptr->data << " | " << node_color << endl;
    inorderBST(ptr->right);
}

// print the tree traversal by inorder
void RedBlackTree::inorder()
{
    inorderBST(root);
}