/*************************************************
Developer: Bryan Pesquera
This header file describes a queue data structure.
**************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
#include<cassert>
using namespace std;

template<class Type>
class Node
{
public:
    Type info;
    Node<Type> * link;

    //constructor
    Node(Type item) : info(item), link(NULL) {}


};//end of Node class

template<class Type>
class Queue
{
private:
    Node<Type> * qfront;
    Node<Type> * qrear;
    //constructor

public:
    Queue();

    //copy
    void copy(const Queue<Type>&);

    //copy constructor
    Queue(const Queue<Type>& other);

    //overloaded assignment operator
    const Queue<Type>& operator=(const Queue<Type>&);

    //destroy queue
    void destroyQueue();

    //destructor
    ~Queue();

    //observers
    int size() const;
    bool empty() const;
    Type front() const;
    Type back() const;
    void print() const;

    //mutators
    void push(Type item);
    void pop();
    void moveToFront(int);

};//end of Queue class

//Queue class implementation
//constructor
template<class Type>
Queue<Type>::Queue() : qfront(NULL), qrear(NULL) {}

//copy
template<class Type>
void Queue<Type>::copy(const Queue<Type>& other)
{
    if(other.empty())
        qfront = qrear = NULL;
    else
    {
        //copy first node
        Node<Type> * current = other.qfront;
        qfront = new Node<Type>(current -> info);
        qrear = qfront;

        current = current -> link;

        while(current != NULL)
        {
            //create and copy next nodes
            qrear -> link = new Node<Type>(current -> info);
            current = current -> link;
            qrear = qrear -> link;
        }//end while
    }//end else
}

//copy constructor
template<class Type>
Queue<Type>::Queue(const Queue<Type>& other)
{
    copy(other);
}

//overloaded assignment operator
template<class Type>
const Queue<Type>& Queue<Type>::operator=(const Queue<Type>& other)
{
    if(this != &other)
    {
        destroyQueue();
        copy(other);
    }
    return *this;
}

//destroy queue
template<class Type>
void Queue<Type>::destroyQueue()
{
    while(!empty())
        pop();
}

//destructor
template<class Type>
Queue<Type>::~Queue()
{
    destroyQueue();
}

//observers
template<class Type>
int Queue<Type>::size() const
{
    int count = 0;
    Node<Type> * current = qfront;
    while(current != NULL)
    {
        count++;
        current = current -> link;
    }//end while
    return count;
}

template<class Type>
bool Queue<Type>::empty() const
{
    return(qfront == NULL);
}

template<class Type>
Type Queue<Type>::front() const
{
    assert(!empty());
    return qfront -> info;
}

template<class Type>
Type Queue<Type>::back() const
{
    assert(!empty());
    return qrear -> info;
}

template<class Type>
void Queue<Type>::print() const
{
    if(empty())
        cout << "Empty list.\n";
    else
    {
        cout << "Elements in list are:\n";
        int limit = size();
        Node<Type> * current = qfront;
        for(int i = 1; i <= limit; i++)
        {
            cout << i << ") " << current -> info << endl;
            current = current -> link;
        }//end for
    }//end else
}

//mutators
template<class Type>
void Queue<Type>::push(Type item)
{
    Node<Type> * newNode = new Node<Type>(item);

    if(empty())
        qfront = newNode;

    else
        qrear -> link = newNode;

    qrear = newNode;
}

template<class Type>
void Queue<Type>::pop()
{
    if(empty())
        cout << "Empty queue, cannot pop.\n";
    else
    {
        Node<Type> * kod;
        kod = qfront;
        qfront = qfront -> link;
        delete kod;

        if(qfront == NULL)
            qrear = NULL;
    }
}

template<class type>
void Queue<type>::moveToFront(int position)
{
    if(empty())
        cout<<"Empty list. Cannot remove.\n";
    else{
        //check for valid position 2 - size
        if(position<=1 || position > size()){
            cout<<"Position ["<<position<<"] is not valid.\n";
        }
        else
        {
            //It has a minimum of 2 nodes
            Node<type> * current = qfront->link;
            Node<type> * previous = qfront;
            for(int i=2; i< position; i++)
            {
                previous=current;
                current=current->link;

            }//end for
            //Adjust pointers
            previous->link=current->link;
            current->link=qfront;
            qfront=current;

            //check for last node, adjust qRear accordingly
            if(current==qrear)
            {
                qrear=previous;

            }//end if
        }//end else
    }//end else
}//end function

#endif // QUEUE_H
