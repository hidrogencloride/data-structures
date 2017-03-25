#ifndef SOLLIST_H
#define SOLLIST_H

#include "unllist.h"

template<class Type>
class SOLList : public UNLList<Type>
{
public:
    //search
    bool search(Type) const;

    //insert
    void insert(Type);
};

//search
template<class Type>
bool SOLList<Type>::search(Type item) const
{
    bool found = false;
    if(UNLList<Type>::isEmpty())
        cout << "Cannot search on empty list.\n";
    else
    {
        Node<Type> *current = UNLList<Type>::head;
        bool stopSearch = false;
        while(current != NULL && !stopSearch)
        {
            if(item <= current->info)
                stopSearch = true;
            else
                current = current -> link;
        }

        if(stopSearch && (current->info == item))
            found = true;
    }

    return found;
}


//insert
template<class Type>
void SOLList<Type>::insert(Type item)
{
    if(!UNLList<Type>::isEmpty() && search(item)) //if not empty and the item was found
        cout << "Item already in list.\n";
    else
    {
        //create and fill a new node
        Node <Type> * newNode = new Node<Type>;
        newNode -> info = item;
        newNode-> link = NULL;

        if(UNLList<Type>::isEmpty()) //if list is empty
            UNLList<Type>::head = newNode;
        else
        {
            Node<Type> * current = UNLList<Type>::head;
            Node<Type> * trail = NULL;
            bool stopSearch = false;
            while(current != NULL && !stopSearch)
            {
                if(item <= current->info)
                    stopSearch = true;
                else
                {
                    trail = current;
                    current = current -> link;
                }
            } //end while
            if(current == UNLList<Type>::head) //to be placed before first node
            {
                newNode->link = UNLList<Type>::head;
                UNLList<Type>::head = newNode;
            }
            else
            {
                trail->link = newNode;
                newNode -> link = current;

            }//end else

        }//end else
    }
}

#endif // SOLLIST_H
