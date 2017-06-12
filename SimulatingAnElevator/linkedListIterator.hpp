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


#ifndef LINKED_LIST_ITERATOR_HPP
#define LINKED_LIST_ITERATOR_HPP

class Iterator
{
	friend class LinkedList<T>;
public:
	Iterator& operator++()
	{
		previous = current;
		current = current->next;
		return *this;
	}

	Iterator operator++(int)
	{
		Iterator result(*this);
		++(*this);
		return result;
	}

	T& operator*()
	{
		return current->value;
	}

	T* operator->()
	{
		return &current->value;
	}

	bool operator==(const Iterator& other)const
	{
		return current == other.current;
	}

	bool operator!=(const Iterator& other)const
	{
		return !(*this == other);
	}

	//Removes from the linked list the element,
	//to which the Iterator points.
	//We assume that the Iterator is pointing to a valid element
	//!!!This function breaks the iterator!!!
	void remove()
	{
		//if this is the first element of the list
		if (previous == NULL)
		{
			owner->pop_front();
		}
		else //there is a previous element
		{
			//if we are removing the last element,
			//we must change the value of the end pointer
			//in the list
			if (current->next == NULL)
				owner->end = previous;

			previous->next = current->next;
			delete current;
		}

		previous = current = NULL;
	}

private:
	Iterator(Node<T> *previous, Node<T> *current, LinkedList<T>* owner)
	:previous(previous)
	, current(current)
	, owner(owner)
	{
	}

	Node<T> *previous;
	Node<T> *current;
	LinkedList<T> *owner;
};
#endif	//LINKED_LIST_ITERATOR_HPP