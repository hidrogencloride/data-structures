/*============================================================================================================================
Description: Unsorted Linked List
Authors: Bryan Pesquera Santiago
Created on: 2016.
============================================================================================================================*/

#ifndef UNLLIST_H
#define UNLLIST_H

//Linked lists are not abstract data types, they are tools used to create abstract data types

#include <iostream>
#include <string>
using namespace std;

template<class Type>
struct Node
{
    Type info;
    Node <Type> *link;
};

template <class Type>
class UNLList
{
protected:  //to be derived
    Node <Type> * head; //pointer to first element in node

private:
    void destroyList();

    //copy constructor
    void copy(const UNLList<Type> &);

public:
    //constructor
    UNLList();

    //copy constructor
    UNLList(const UNLList&);

    //overloaded assignment operator
    const UNLList<Type>& operator=(const UNLList<Type>&);

    //destructor
    ~UNLList();

    //Getters
    bool isEmpty() const;
    bool isFull() const;
    int length() const;
    bool search(const Type&) const;
    void print() const;

    //Setters
    void insert(Type);
    void remove(Type);
    void clear();
};

//constructor
template <class Type>
UNLList<Type>::UNLList() : head(NULL) {}

//copy constructor
template<class Type>
UNLList<Type>::UNLList(const UNLList<Type>& other)
{
    copy(other);
}

//overloaded assignment operator
template<class Type>
const UNLList<Type>& UNLList<Type>::operator=(const UNLList<Type>& other)
{
    //this is a pointer
    if(this != &other)
    {
        //avoid self assignment

        if(!isEmpty()) //if list is empty, there is nothing to destroy
            destroyList();

        copy(other);
    }
    return *this; //return el objeto al cual el puntero apunta
}

//destructor
template <class Type>
UNLList<Type>::~UNLList()
{
    destroyList();
}

//destroy list
template <class Type>
void UNLList<Type>::destroyList()
{
    Node<Type> * kod;
    while(head != NULL)
    {
        kod = head;
        head = head -> link;
        delete kod;
    }

    /* PREVIOUS FUNCTION AS A FOR LOOP

        for(int kod = head; head != NULL; kod = head)
        {
            head = head -> link;
            delete kod;
        }
    */
}

//Getters
template<class Type>
bool UNLList<Type>::isEmpty() const
{
    return (head == NULL);
}

template<class Type>
bool UNLList<Type>::isFull() const
{
    bool isFull;
    Node<Type> * temp; //not a node, its a pointer to a node
    temp = new Node<Type>;
    if(temp == NULL)
        isFull = true;
    else
    {
        isFull = false;
        delete temp; //delete temporary pointer to node
    }
    return isFull;
}

template<class Type>
int UNLList<Type>::length() const
{
    int count = 0; //count nodes
    Node <Type> * current = head; //use a copy of head to not change head's value
    while(current != NULL)
    {
        count++;
        current = current -> link;
    }
    return count;
}

template<class Type>
bool UNLList<Type>::search(const Type& item) const
{
    bool found = false;
    if (isEmpty())
        cout <<"Empty list.\n";
    else
    {
        //proceed to linear search
        Node<Type> * current = head;
        while(current != NULL && !found) //while list is not over and item is not found
        {
            if(item == current -> info)
                found = true;
            else
                current = current -> link;
        }
    }
    return found;
}

template<class Type>
void UNLList<Type>::print() const
{
    if(isEmpty())
        cout << "Empty list.\n";
    else
    {
        cout << "Elements in list: \n";
        Node<Type> * current = head;
        for(int i = 1; i <= length(); i++)
        {
            cout << "(" << i << ") " << current -> info << endl;
            //check this
            current = current->link;
        }
    }
}

//Setters
template<class Type>
void UNLList<Type>::insert(Type item)
{
    if(!isEmpty() && search(item))
        cout << "Item already in list.\n";
    else
    {
        Node <Type> * newNode = new Node<Type>;
        newNode -> info = item;
        newNode -> link = NULL;

        //insert
        if(isEmpty())
            head = newNode;
        else
        {
            Node<Type> * current = head;
            while(current -> link != NULL)
            current = current -> link;

            //insert
            current -> link = newNode;
        }

     }
}

template<class Type> //check
void UNLList<Type>::remove(Type item)
{
    if(isEmpty())
        cout << "Cannot remove from empty list.\n";
    else if(!search(item))
        cout << item << " not in list.\n";
    else
    {
        //check for removal of first node
        if(head->info == item)
        {
            Node<Type> * kod = head;
            head = head -> link;
            delete kod;
        }
        else
        {
            Node<Type> * current = head -> link;
            Node<Type> * previous = head;

            while(current -> info != item)
            {
                previous = current;
                current = current -> link;

            }//end while

            //link previous with next
            previous -> link = current -> link;
            //check this
            delete current;
        }
    }
}

template<class Type>
void UNLList<Type>::clear()
{
    destroyList();
}

//copy constructor
template<class Type>
void UNLList<Type>::copy(const UNLList<Type> &original)
{
    if(original.isEmpty())
        head = NULL;
    else
    {
        //copy first node
        Node<Type> * current = other.head;
        Node<Type> * newNode;

        head = new Node<Type>;
        head->info = current -> info;
        head->link = NULL;

        //to copy the remaining nodes
        Node<Type> * previous = head;

        current = current -> link;
        while(current != NULL)
        {
            //create new node
            newNode = new Node<Type>;
            newNode -> info = current -> info;
            newNode -> link = NULL;

            //insert node
            previous->link = newNode;

            //move forward both pointers
            previous = previous ->link;
            current = current->link;
        }//end while
    }
}

#endif // UNLLIST_H
