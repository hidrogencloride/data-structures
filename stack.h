/*============================================================================================================================
Description: Stack
Authors: Bryan Pesquera Santiago
Created on: 2016.
============================================================================================================================*/

#ifndef STACK_H
#define STACK_H
#ifndef STACK001_H
#define STACK001_H
#include <iostream>
#include <cassert>

using namespace std;

template<class Type>
class Node
{
public:

    Type info;
    Node <Type> * link;

    //constructor
    //with info parameter
    Node(Type item) : info(item), link(NULL) {}

}; //end of node class

//stack
template<class Type>
class stack
{
private:

    Node <Type> * topPtr;

    //copy
    void copy(const stack<Type>&);

public:

    //constructor
    stack();

    //copy constructor
    stack(const stack<Type> &);

    //destructor
    ~stack();

    //getters
    bool empty() const;
    int size() const;
    Type top() const;
    void print() const;

    //setters
    void push(Type);
    void pop();
    void initStack(); //initializes stack
                      //eliminates stack and creates new

    //overloaded assignment operator
    const stack<Type>& operator=(const stack<Type>&);

}; //end of class stack

                            //class stack implementation
//constructor
template<class Type>
stack<Type>::stack() : topPtr(NULL) {}

//destructor
template<class Type>
stack<Type>::~stack()
{
    initStack();
}

//getters
template<class Type>
bool stack<Type>::empty() const
{
    return(topPtr == NULL);
}

template<class Type>
int stack<Type>::size() const
{
    int count = 0;
    Node<Type> * current = topPtr;
    while(current != NULL)
    {
        count++;
        current = current -> link;
    }//end while
    return count;
}

template<class Type>
Type stack<Type>::top() const
{
    assert(topPtr!=NULL); //if true, it continues
                           //else if false, it aborts
    return topPtr -> info;
}

template<class Type>
void stack<Type>::print() const
{
    if(empty())
        cout << "Empty stack.\n";
    else
    {
        cout << "Elements in stack are: \n";
        Node <Type> * current = topPtr;

        for(int i = 1; i <= size(); i++)
        {
            cout << i << ") " << current -> info << endl;
            current = current -> link;
        }//end for
    }//end else
}

//setters
template<class Type>
void stack<Type>::push(Type item)
{
    Node<Type> * newNode = new Node<Type>(item);
    newNode -> link = topPtr;
    topPtr = newNode;
}

template<class Type>
void stack<Type>::pop()
{
    if(empty())
        cout << "Empty stack, cannot pop.\n";
    else
    {
        Node<Type> * kod = topPtr;
        topPtr = topPtr -> link;
        delete kod;
    }//end else
}

template<class Type>
void stack<Type>::initStack()
{
    Node <Type> * kod;
         while(topPtr != NULL)
         {
            kod = topPtr;
            topPtr = topPtr -> link;
            delete kod;
         }//end while

    /* Function could also be as: */
         /* while(!empty())
                pop(); */
}

//copy
template<class Type>
void stack<Type>::copy(const stack<Type>& other)
{
    if(other.empty())
        topPtr = NULL;
    else
    {
        Node <Type> * original;
        Node <Type> * copy;

        topPtr = new Node<Type>(other.topPtr->info);

        original = other.topPtr->link;

        copy = topPtr;

        while(original != NULL)
        {
            copy->link = new Node<Type>(original->info);
            original = original -> link;
            copy = copy -> link;
        }//end while
    }//end else
}

//copy constructor
template<class Type>
stack<Type>::stack(const stack<Type>& other)
{
    copy(other);
}

//overloaded assignment operator
template<class Type>
const stack<Type>& stack<Type>::operator=(const stack<Type>& other)
{
    if(this != &other)
    {
        initStack();
        copy(other);
    }
    return *this;
}

#endif // STACK001_H

#endif // STACK_H
