
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

#ifndef PLINKED_QUEUE_
#define PLINKED_QUEUE_

#include "PriNode.h"
#include "PQueueADT.h"
using namespace std;


template <typename T>
class PriQ :public PQueueADT<T>
{
private:

	PriNode<T>* backPtr;
	PriNode<T>* frontPtr;
	int count;

public:
	PriQ();
	PriNode<T>* newNode(T& d, int& p);
	bool isEmpty() const;
	bool enqueue(const T& data, const int& priority);
	bool dequeue(T& frntEntry);
	int get_count();
	PriNode<T>* getPFront() const;
	bool peek(T& frntEntry)  const;
	~PriQ();

	//copy constructor
	PriQ(const PriQ<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.
*/

template <typename T>
PriQ<T>::PriQ()
{
	count = 0;
	frontPtr = nullptr;
	backPtr = nullptr;
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
bool PriQ<T>::enqueue(const T& data, const int& priority)
{
	PriNode<T>* start = frontPtr;

	// Create new Node
	PriNode<T>* temp = new PriNode<T>(data, priority);
	if (!frontPtr) {
		frontPtr = temp;
		frontPtr->setPrio(priority);
		++count;
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
		temp->setNext(start->getNext());
		start->setNext(temp);
	}
	++count;
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

	PriNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	--count;

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
template<typename T>
PriNode<T>* PriQ<T>::getPFront() const
{
	return frontPtr;
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
	count = 0;
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
PriQ<T>::PriQ(const PriQ<T>& LQ)
{
	PriNode<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		count++;
		return;
	}

	//insert the first node
	PriNode<T>* ptr = new PriNode<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();
	++count;
	//insert remaining nodes
	while (NodePtr)
	{
		PriNode<T>* ptr = new PriNode<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
		++count;
	}
}
template <typename T>
int PriQ<T>::get_count() {
	return count;
}

#endif