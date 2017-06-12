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

#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "node.h"

namespace fmi
{
	namespace sdp
	{

		template<typename T>
		class LinkedList
		{
			friend class Iterator;
		public:
			LinkedList();

			LinkedList(const LinkedList<T>& other);

			LinkedList<T>& operator=(const LinkedList<T>& other);

			~LinkedList();

		public:
			bool isEmpty() const;

			void push_back(const T& value);

			T pop_front();

		public:

#include "linkedListIterator.hpp"

			Iterator beginIterator()
			{
				return Iterator(NULL, begin, this);
			}
			Iterator endIterator()
			{
				return Iterator(end, NULL, this);
			}
		private:

			//frees the dinamically allocated memory
			void clear();

			//assigns NULL to the begin pointer and end pointer
			void makeNULL();

			static void copyList( Node<T>*& newListBegin, Node<T>*& newListEnd, const Node<T>* oldListBegin);

			Node<T>* begin;
			Node<T>* end;

		};

#include "linkedListRealization.hpp"

	} //sdp
} //fmi


#endif	//LINKED_LIST_H