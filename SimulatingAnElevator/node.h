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


#ifndef NODE_H
#define NODE_H

namespace fmi
{
	namespace sdp
	{

		template<typename T>
		struct Node
		{
			Node()
			{
				next = NULL;
			}

			Node(const T& value, Node<T>* next = NULL)
				: value(value)
				, next(next)
			{
			}

			T value;
			Node<T> *next;
		};


	} //sdp
} //fmi

#endif	//NODE_H