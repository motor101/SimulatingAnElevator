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


#ifndef LINKED_LIST_REALIZATION_HPP
#define LINKED_LIST_REALIZATION_HPP
#include<stdexcept>

template<typename T>
inline LinkedList<T>::LinkedList()
{
	makeNULL();
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
	copyList(begin, end, other.begin);
}

template<typename T>
inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
	if (this != &other)
	{
	
	Node<T>* newListBegin;
	Node<T>* newListEnd;

	copyList(newListBegin, newListEnd, other.begin);

	clear();

	begin = newListBegin;
	end = newListEnd;
	}
	return *this;
}


template<typename T>
inline LinkedList<T>::~LinkedList()
{
	clear();
}

template<typename T>
inline bool LinkedList<T>::isEmpty() const
{
	return begin == NULL;
}

template<typename T>
inline void LinkedList<T>::push_back(const T& value)
{
	if (isEmpty())
	{
		begin = end = new Node<T>(value, NULL);
	}
	else
	{
		end->next = new Node<T>(value, NULL);
		end = end->next;
	}
}


template<typename T>
inline T LinkedList<T>::pop_front()
{
	//If there is no element in the list
	if (isEmpty())
		throw std::exception("The list is empty");

	//This is the result ot the function
	T result = begin->value;

	//if there is only 1 element in the list,
	//the list will become empty
	if (begin == end)
		clear();

	else
	{
		Node<T>* previous = begin;

		begin = begin->next;

		delete previous;
	}

	return result;
}


//frees the dinamically allocated memory
template<typename T>
inline void LinkedList<T>::clear()
{
	Node<T> *current = begin;
	Node<T> *previous;

	while (current != NULL)
	{
		previous = current;
		current = current->next;
		delete previous;
	}

	makeNULL();
}

//assigns NULL to the begin pointer and end pointer
template<typename T>
inline void LinkedList<T>::makeNULL()
{
	begin = NULL;
	end = NULL;
}

//creates a new LinkedList starting with pointers:
//newListBegin and newListEnd
//This new list is a copy of the an old list
template<typename T>
inline void LinkedList<T>::copyList(Node<T> *&newListBegin, Node<T> *&newListEnd, const Node<T>* oldListBegin)
{
	//if the old List is empty,
	//the new list will also be empty
	if (oldListBegin == NULL)
	{
		newListBegin = NULL;
		newListEnd = NULL;
		return;
	}

	//the old list isn't empty, so we have to ensure the newListBegin
	//points to a value
	newListBegin = newListEnd = new Node<T>(oldListBegin->value, NULL);

	//this pointer will be used to scan the elements of the
	//old list one by one
	const Node<T>* pointerForScanningTheOldList = oldListBegin->next;

	//scanning all the elements in the old list
	while (pointerForScanningTheOldList)
	{
		newListEnd->next = new Node<T>(pointerForScanningTheOldList->value, NULL);

		newListEnd = newListEnd->next;

		pointerForScanningTheOldList = pointerForScanningTheOldList->next;
	}
}


#endif	//LINKED_LIST_REALIZATION_HPP