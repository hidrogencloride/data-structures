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
