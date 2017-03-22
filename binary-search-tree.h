/********************************************************
Developer: Bryan Pesquera
This header file describes a binary tree data structure.
********************************************************/

#ifndef BT_H
#define BT_H
#include <iostream>

using namespace std;

template<class Type>
struct Node
{
    //members in struct is by default public
    Type info;
    Node<Type> * llink; //left subtree
    Node<Type> * rlink; //right subtree

    Node(Type item) : info(item), llink(NULL), rlink(NULL) {}
}; //end of Node struct

template<class Type>
class BT //class binary tree is base class for binary search tree
{
protected:
    Node<Type> * root;

public:

    //constructor
    BT();

    //destructor
    ~BT();

    //destroy tree, clear function
    //that empties the tree
    void destroyTree();

    //observers
    bool isEmpty() const;
    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;
    void inOrderTraversal() const; //prints to screen

    //overloaded assignment operator
    const BT<Type>& operator=(const BT<Type>&);

    //copy constructor
    void copyTree(Node<Type> &, Node<Type> *);

private:

    void copyTree(Node<Type> * &, Node<Type> *);

    //helper functions implemented recursively
    void destroy(Node<Type> *&);

    //height = number of edges on longest path
    int height(Node<Type> *) const;

    //returns longest path on either side
    int max(int, int) const;

    int nodeCount(Node<Type> *) const;
    int leavesCount(Node<Type> *) const;
    void inOrder(Node<Type> *) const;

};

#endif // BT_H

//wrapper functions call helper (recursive) functions

//class impementation
//constructor
template<class Type>
BT<Type>::BT() : root(NULL) {}

template<class Type>
void BT<Type>::copyTree(Node<Type> * & copy, Node<Type> *original)
{
    if(original == NULL)
        copy=NULL;

    else{
        copy =new Node<Type>(original->info);
        copyTree(copy->llink, original->llink);//leftLink
        copyTree(copy->rlink, original->rlink);//rightLink
    }
}

//assignment operator overloaded
template<class Type>
const BT<Type> & BT<Type>::operator=(const BT<Type>& other)
{
    if(this != other) //avoids self assignment
    {
        if(root != NULL)
            destroy(root);

        copyTree(root,other.root);
    }
    return *this; //returns object, not pointer
}

//destructor
template<class Type>
BT<Type>::~BT()
{
    destroy(root);
}

//destroy tree
template<class Type>
void BT<Type>::destroyTree()
{
    destroy(root);
}

//observers
template<class Type>
bool BT<Type>::isEmpty() const
{
    return(root == NULL);
}

template<class Type>
int BT<Type>::treeHeight() const
{
    //invoke helper function
    return(height(root));
}

template<class Type>
int BT<Type>::treeNodeCount() const
{
    return(nodeCount(root));
}

template<class Type>
int BT<Type>::treeLeavesCount() const
{
    return(leavesCount(root));
}

template<class Type>
void BT<Type>::inOrderTraversal() const
{
    if(isEmpty())
        cout << "Empty tree.\n";
    else
        inOrder(root);
}

//helper functions implemented recursively
template<class Type>
void BT<Type>::destroy(Node<Type> *&ptr)
{
    //not tail end recursive
    if(ptr != NULL)
    {
        destroy(ptr->llink);
        destroy(ptr->rlink);
        delete ptr;
        ptr = NULL;
    }
}

template<class Type>
int BT<Type>::height(Node<Type> *ptr) const
{
    //base case when root == NULL
    if(ptr == NULL)
        return -1;
    else
        //not tail end recursive
        return 1 + max(height(ptr->llink),
                       height(ptr->rlink));
}

//returns longest path on either side
template<class Type>
int BT<Type>::max(int l, int r) const
{
    return(l >= r ? l : r);
}

template<class Type>
int BT<Type>::nodeCount(Node<Type> *ptr) const
{
    if(ptr == NULL)
        return 0;
    else
    {
        return (1 + nodeCount(ptr -> llink) //count nodes on left subtree
                  + nodeCount(ptr -> rlink)); //count nodes on right subtree
    }
}

template<class Type>
int BT<Type>::leavesCount(Node<Type> *ptr) const
{
    if(ptr == NULL) //base case 1
        return 0;
    else    //base case 2
    {
       if(ptr -> llink == NULL && ptr -> rlink == NULL) //base
           return 1;
       else
           return(leavesCount(ptr -> llink)
                  + leavesCount(ptr -> rlink));
    }
}

template<class Type>
void BT<Type>::inOrder(Node<Type> *ptr) const
{
    if(ptr != NULL)
    {
        inOrder(ptr -> llink); //left subtree
        cout << ptr -> info << endl; //displays both nodes
        inOrder(ptr -> rlink); //right subtree
    }
}

/***************************************************************
Developer: Bryan Pesquera
This header file describes a binary search tree data structure.
***************************************************************/

//class: binary search tree bst.h
//derived from binary tree bt.h

#ifndef BST_H
#define BST_H

#include "bt.h"
#include <cassert>

template<class Type>
class BST : public BT<Type> //binary search tree or also binary ordered tree
{
public:

    bool search(Type) const;
    //could also be bool search(const Type &);

    void insert(Type);

    Type findMin() const;

    Type findMax() const;

}; //end of class BST declaration

#endif // BST_H

//class implementation

template<class Type>
bool BST<Type>::search(Type item) const
{
    bool found = false;
    Node<Type> * current = BT<Type>::root;

    while(current != NULL && !found)
    {
        if(item < current -> info)
            current = current -> llink;
        else if(item > current -> info)
            current = current -> rlink;
        else
            found = true;
    }//end while
    return found;
}

template<class Type>
void BST<Type>::insert(Type item)
{
    //always insert on leaves
    bool found = false;
    Node<Type> * current = BT<Type>::root;
    Node<Type> * parent = NULL;

    //search for insertion place
    while(current != NULL && !found)
    {
        //move parent
        parent = current;

        //move current
        if(item < current -> info)
            current = current -> llink;
        else if(item > current -> info)
            current = current -> rlink;
        else
            found = true;
    }//end while

    if(found)
        cout << "Item is already in tree.\n";
    else
    {
        //insert
        Node<Type> * newNode = new Node<Type>(item);

        if(parent == NULL)
            BT<Type>::root = newNode;
        else if(item < parent -> info)
            parent -> llink = newNode;
        else
            parent -> rlink = newNode;
    }//end else
}//end function

//goes to the left most node
template<class Type>
Type BST<Type>::findMin() const
{
    assert(!isEmpty());
    Node<Type> * current = root;
    while(current -> llink!=NULL)
        current = current ->llink;

    return current ->info;
}

//goes to the right most node
template<class Type>
Type BST<Type>::findMax() const
{
    assert(!isEmpty());
    Node<Type> * current = root;
    while(current -> rlink!=NULL)
        current = current ->rlink;

    return current -> info;
}

