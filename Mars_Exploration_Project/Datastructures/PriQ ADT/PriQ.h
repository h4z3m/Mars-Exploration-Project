
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The Node: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontPtr	 backptr
\	 /
\	/
---- NULL ------


Single Node Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include "QueueADT.h"
using namespace std;


template <typename T>
class PriQ :public QueueADT<T>
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;

public:
	PriQ();
	Node<T>* newNode(T& d, T& p);
	bool isEmpty() const;
	bool enqueue(const T& data, const T& priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~PriQ();

	//copy constructor
	PriQ(const PriQ<T> & LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriQ<T>::PriQ()
{
	frontPtr = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

//template <typename T>
//Node<T>* PriQ<T>::newNode(T& data, T& prio)
//{
//	Node<T>* temp = (Node*)malloc(sizeof(Node));
//	temp->setItem(data);
//	temp->setPrio(prio);
//
//	temp->setNext(nullptr);
//
//	return temp;
//}

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriQ<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriQ<T>::enqueue(const T& data, const T& priority)
{
	Node<T>* start = frontPtr;

	// Create new Node
	Node<T>* temp = new Node<T>(data, priority);
	if (!frontPtr) {
		frontPtr = temp;
		frontPtr->setPrio(priority);
		return true;
	}
	// Special Case: The head of list has
	// lesser priority than new node. So
	// insert newnode before head node
	// and change head node.
	if (frontPtr->getPrio() < priority)
	{

		// Insert New Node before head
		temp->setNext(frontPtr);
		frontPtr = temp;
	}
	else
	{

		// Traverse the list and find a
		// position to insert new node
		while (start->getNext() != nullptr &&
			start->getNext()->getPrio() > priority)
		{
			start = start->getNext();
		}

		// Either at the ends of the list
		// or at required position
		temp->setNext(start->getNext()) ;
		start->setNext(temp);
	}
	return true;
}

/*template <typename T>
bool PriQ<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue*/


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T>
bool PriQ<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool PriQ<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
PriQ<T>::~PriQ()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: PriQ<T>: The Queue to be copied
Output: none
*/

template <typename T>
PriQ<T>::PriQ(const PriQ<T> & LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif