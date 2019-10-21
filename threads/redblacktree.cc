//
// Red Black Tree Implementation
//
#include <bits/stdc++.h>
#include "redblacktree.h"
using namespace std;

Node::Node(int data)
{
    this->data = data;
    color = RED;
    left = right = parent = NULL;
}

RBTree::RBTree()
{
    root = NULL;
}

int Node::getColor()
{
    if (this != NULL)
        return this->color;

    return BLACK;
}

void Node::setColor(int color)
{
    if (this != NULL)
        this->color = color;
}

Node *RBTree::getRoot()
{
    return root;
}

Node *RBTree::insertBST(Node *&root, Node *&ptr)
{
    if (root == NULL)
        return ptr;

    if (ptr->data > root->data)
    {
        root->right = insertBST(root->right, ptr);
        root->right->parent = root;
    }
    else if (ptr->data <= root->data)
    {
        root->left = insertBST(root->left, ptr);
        root->left->parent = root;
    }
    return root;
}

void RBTree::insertValue(int n, Thread *&reqThread)
{
    Node *node = new Node(n);
    node->reqThread = reqThread;
    root = insertBST(root, node);
    fixInsertRBTree(node);
}

void RBTree::rotate(string rotateNode, Node *&ptr, Node *&child, bool rotateFlag)
{
    if (rotateFlag)
    {
        child->parent = ptr->parent;
        if (ptr->parent == NULL)
            root = child;
        else if (ptr == ptr->parent->left)
            ptr->parent->left = child;
        else
            ptr->parent->right = child;
    }
}

void RBTree::rotateLeft(Node *&ptr)
{
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != NULL)
        ptr->right->parent = ptr;

    rotate("left", ptr, right_child, true);

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr)
{
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != NULL)
        ptr->left->parent = ptr;

    rotate("right", ptr, left_child, true);

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::changeNodeColor(Node *&ptr, string pos)
{
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
        if (pos == "left")
        {
            if (ptr == parent->right)
            {
                rotateLeft(parent);
                ptr = parent;
                parent = ptr->parent;
            }
            rotateRight(grandparent);
            swap(parent->color, grandparent->color);
            ptr = parent;
        }
        else
        {
            if (ptr == parent->left)
            {
                rotateRight(parent);
                ptr = parent;
                parent = ptr->parent;
            }
            rotateLeft(grandparent);
            swap(parent->color, grandparent->color);
            ptr = parent;
        }
    }
}
void RBTree::fixInsertRBTree(Node *&ptr)
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

void RBTree::fixDeleteRBTree(Node *&node)
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
                    sibling->setColor(BLACK);
                    parent->setColor(RED);
                    rotateLeft(parent);
                }
                else
                {
                    if (sibling->left->getColor() == BLACK && sibling->right->getColor() == BLACK)
                    {
                        sibling->setColor(RED);
                        if (parent->getColor() == RED)
                            parent->setColor(BLACK);
                        else
                            parent->setColor(DOUBLE_BLACK);
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
                        if (parent->getColor() == RED)
                            parent->setColor(BLACK);
                        else
                            parent->setColor(DOUBLE_BLACK);
                        ptr = parent;
                    }
                    else
                    {
                        if (sibling->left->getColor() == BLACK)
                        {
                            sibling->right->setColor(BLACK);
                            sibling->setColor(RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        sibling->setColor(parent->color);
                        parent->setColor(BLACK);
                        sibling->left->setColor(BLACK);
                        rotateRight(parent);
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

Node *RBTree::deleteBST(Node *&root, Node *&dNode, int data)
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

void RBTree::deleteValue(int data, Node *&ptr)
{
    Node *node = deleteBST(root, ptr, data);
    fixDeleteRBTree(node);
}

void RBTree::inorderBST(Node *&ptr)
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

void RBTree::inorder()
{
    inorderBST(root);
}

Node *RBTree::minValueNode(Node *&node)
{

    Node *ptr = node;

    while (ptr->left != NULL)
        ptr = ptr->left;

    return ptr;
}

void RBTree::printTree()
{
    inorder();
}