/********************************************************
Developer: Bryan Pesquera
This header file describes a list data structure.
********************************************************/

#pragma once
#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

class List
{
protected:			//so derived classes have access
	int maxSize,	//physical size
		length,		//logical size
		*list;		//list pointer
	//copy function used by copy construtor and overloaded assignment operator=
	void copy(const List&);

public:

	//constructor
	List(int = 100);
	
	//copy constructor
	List(const List&); //copy needs to get original object before copying, call by reference

	//overloaded assignment operator
	const List& operator=(const List &);

	//destructor
	~List();

	//observers, getters
	bool isEmpty() const;
	bool isFull() const;
	int listSize() const;
	int listLength() const;
	int search(int) const;
	void print() const;

	//mutators, setters
	void insert(int);	//derived class 'sorted list' is implemented here
	void remove(int);
	void clear();
};

#endif

//constructor
List::List(int size) 
{
	maxSize = (size > 1) ? size : 100;
	length = 0;
	list = new int[maxSize];
}

void List::copy(const List&original)
{
	//copy values
	maxSize = original.maxSize;
	length = original.length;

	//create list
	list = new int[maxSize];

	//copy list
	for (int i = 0; i < length; i++)
	{
		list[i] = original.list[i];
	}
}

//copy constructor
List::List(const List&original)
{
	copy(original);
}

//overloaded assignment operators, same as copy constructor
//const List& allows for multiple assignments a = b = c
const List& List::operator=(const List & original)
{
	//check that it is not self assignment ex.: list = list;
	//avoid self assignment
	if (this != &original)
	{		//avoid garbage
			delete[] list;
			copy(original);
	}
	//return self object
	//first dereference pointer and return
	return *this;
}

//destructor
List::~List()
{
	delete [] list;
	list = NULL;
}

//observers, getters
bool List::isEmpty() const
{
	return length == 0;
}

bool List::isFull() const
{
	return length == maxSize;
}

int List::listSize() const
{
	return maxSize;
}

int List::listLength() const
{
	return length;
}

int List::search(int item) const
{
	int position = -1;
	bool found = false;

	//linear or sequential search
	for (int i = 0; i < length && !found; i++)
	{
		if (item == list[i])
		{
			position = i;
			found = true;
		}
	}
	return position;
}

void List::print() const
{
	if (isEmpty())
		cout << "EMPTY LIST\n";
	else
	{
		cout << "Elements in list are:\n";
		for (int i = 0; i < length; i++)
		{
			cout << (i + 1) << ": "
				<< (list[i]) << endl;
		}
	}
		
}

//mutators, setters
void List::insert(int item)
{
	if (isFull())	//case 1
		cout << "LIST IS FULL.\n";
	else if (search(item) >= 0)	//case 2
		cout << "ITEM ALREADY IN LIST.\n";
	else	//insert item
	{
		list[length++] = item;	//increment length after inserting value to length
	}
}

void List::remove(int item)
{
	if (isEmpty()) //case 1
		cout << "EMPTY LIST\n";
	else	//case 2
	{
		int location = search(item);
		if (location == -1)
			cout << item << " NOT FOUND\n";
		else
		{
			list[location] = list[length - 1];
			length--;
		}
	}

}

void List::clear()
{
	length = 0;
}

/**************************************************************
Developer: Bryan Pesquera
This header file describes a sorted array list data structure.
**************************************************************/

#pragma once
#include "List.h"

#ifndef SALIST_H
#define SALIST_H

class SAList : public List
{
public:
	//constructor
	SAList(int = 100);
	
	//redefined function
	int search(int) const; //getter does not alter, so we put const
	void insert(int);		//changes the list, so no const
	void remove(int);		//changes the list, so no const

};
//end of class declaration
#endif // !SOLIST_H

SAList::SAList(int ms) : List(ms) {} //calls constructor of base class and initializes mazSize to 100

//will return position of item in list
int SAList::search(int item) const
{
	//binary search
	int position = -1;
	bool found = false;
	int first = 0,
		last = length - 1,
		middle;

	while ((first <= last) && !found)
	{
		middle = (first + last) / 2;
		if (item == list[middle])
		{
			found = true;
			position = middle;
		}
		else if (item < list[middle])
		{
			last = middle - 1;
		}
		else if (item > list[middle])
		{
			first = middle + 1;
		}
	}
	return position;
}

void SAList::insert(int item)
{
	if (isFull())
		cout << "List is full, cannot add '" << item << "'\n";
	else if (search(item) != -1)
		cout << "Item already in list.\n";
	else
	{

		int location = 0;
		while (location < length && item > list[location])
		{
			location++;
		}

		for (int i = length; i > location; i--)
			list[i] = list[i - 1];

		//insert
		list[location] = item;
		
		//adjust length after insertion
		length++;
	}
}

void SAList::remove(int item)
{
	if (isEmpty())
		cout << "Empty List, cannot remove component.";
	else
	{
		int location = search(item);
		if (location == -1)
			cout << item << " is not found in list.";

		else //proceed with remotion
		{
			for (int i = location + 1; i < length; i++)
				list[i - 1] = list[i];
			
			//ajustar length
			length--;
		}
	}
}
