/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kamen Ivanov
* @idnumber 61894
* @task 2
* @compiler VC
*
*/

#include "stdafx.h"
#include<iostream>
#include "stack.h"
#include "linkedList.h"

using namespace std;
using namespace fmi::sdp;

//tests the methods of class Stack<T>
void stackTest()
{
	//default ctor
	Stack<int> stack1;

	//getSize()
	cout << "size of stack1 = " << stack1.getSize() << endl;

	//getCapacity()
	cout << "capacity of stack1 = " << stack1.getCapacity() << endl;

	//push
	for (int i = 0; i < Stack<int>::defaultCapacity; ++i)
		stack1.push(i);

	//isFull()
	cout << "stack1 is " << (stack1.isFull() ? "" : "not ") << "full\n";

	cout << "size of stack1 = " << stack1.getSize() << endl;
	cout << "capacity of stack1 = " << stack1.getCapacity() << endl;

	//isEmpty
	cout << "stack1:\n";
	while (!stack1.isEmpty())
	{
		//pop()
		cout << stack1.pop() << ' ';
	}
	cout << endl;

	cout << "size of stack1 = " << stack1.getSize() << endl;
	cout << "capacity of stack1 = " << stack1.getCapacity() << endl;

	for (int i = 0; i < 2 * Stack<int>::defaultCapacity; ++i)
		stack1.push(i);

	cout << "size of stack1 = " << stack1.getSize() << endl;
	cout << "capacity of stack1 = " << stack1.getCapacity() << endl;


	cout << "size of stack1 = " << stack1.getSize() << endl;
	cout << "capacity of stack1 = " << stack1.getCapacity() << endl;

	//copy ctor
	Stack<int>stack2(stack1);
	cout << "stack2:\n";
	while (!stack2.isEmpty())
	{
		cout << stack2.pop() << ' ';
	}
	cout << endl;

	cout << "size of stack2 = " << stack2.getSize() << endl;
	cout << "capacity of stack2= " << stack2.getCapacity() << endl;

	//operator=
	cout << "stack2=stack1\n";
	stack2 = stack1;
	cout << "size of stack2= " << stack2.getSize() << endl;
	cout << "capacity of stack2= " << stack2.getCapacity() << endl;


	cout << "stack2:\n";
	while (!stack2.isEmpty())
	{
		cout << stack2.pop() << ' ';
	}
	cout << endl;

	cout << "size of stack2= " << stack2.getSize() << endl;
	cout << "capacity of stack2= " << stack2.getCapacity() << endl;

}


//prints out the elements of the linked list
template <typename T>
void print(LinkedList<T>& list, const char* nameOfList)
{
	cout << nameOfList << " : ";

	LinkedList<T>::Iterator it = list.beginIterator();

	while (it != list.endIterator())
	{
		cout << *it << ' ';
		++it;
	}
	cout << endl;
}

//tests the methods of class LinkedList
//and its iterator
void linkedListTest()
{
	//tests default ctor
	LinkedList<int> list1;

	for (int i = 0; i < 10; ++i)
		list1.push_back(i);

	print(list1, "list1");

	//remove an element from the middle of the list
	LinkedList<int>::Iterator  it = list1.beginIterator();
	while (it != list1.endIterator())
	{
		if (*it == 2)
		{
			it.remove();
			break;
		}
		it++;
	}


	//remove the first element
	it = list1.beginIterator();
	while (it != list1.endIterator())
	{
		if (*it == 0)
		{
			it.remove();
			break;
		}
		it++;
	}

	//remove the last element
	it = list1.beginIterator();
	while (it != list1.endIterator())
	{
		if (*it == 9)
		{
			it.remove();
			break;
		}
		it++;
	}

	print(list1, "list1");

	//tests copy ctor
	LinkedList<int> list2(list1);

	cout << "copy ctor:\n";
	print(list2, "list2");

	cout << "removing first element of list1:\n";
	list1.pop_front();

	print(list1, "list1");

	//tests assignment operator
	list2 = list1;

	cout << "list2=list1:\n";
	list2 = list2;
	print(list2, "list2");

	cout << "removing elements of list2 one by one:\n";

	while (!list2.isEmpty())
	{
		list2.pop_front();
		print(list2, "list2");
	}

	list2 = list1;

	cout << "removing elements of list2 one by one:\n";
	while (!list2.isEmpty())
	{
		list2.beginIterator().remove();
		print(list2, "list2");
	}

}
