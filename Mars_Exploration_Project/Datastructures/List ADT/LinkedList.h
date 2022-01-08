#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "LNode.h"
#include <iostream>
template <typename T>
class LinkedList
{
private:
	LNode<T>* Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;

public:


	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll();
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all LNodes in a linked list.
	*/
	void PrintList()	const
	{
		cout << "\nprinting list contents:\n\n";
		LNode<T>* p = Head;

		while (p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new LNode and adds it to the beginning of a linked list.
	*
	* Parameters:
	*	- data : The value to be stored in the new LNode.
	*/
	void InsertBeg(const T& data)
	{
		LNode<T>* R = new LNode<T>(data);
		R->setNext(Head);
		Head = R;
		++count;

	}
	//[1]InsertEnd 
	//inserts a new LNode at end if the list
	void InsertEnd(const T& data)
	{
		LNode<T>* new_node = new LNode<T>(data);

		LNode<T>* last = Head;
		new_node->setNext(NULL);
		if (Head == NULL)
		{
			Head = new_node;
			return;
		}
		while (last->getNext() != NULL)
		{
			last = last->getNext();
		}
		
		last->setNext(new_node);
		return;
		++count;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all LNodes of the list.
	*/
	void DeleteAll()
	{
		LNode<T>* P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	int getCount()
	{
		int count = 0;
		LNode<T>* current = Head;
		while (current != nullptr)
		{
			count++;
			current = current->getNext();
		}
		return count;
	}
	template <typename T>
	void InsertPosition(T data, int position)
	{
		if (Head == nullptr)
			return;
		else if (position < 1 || position > getCount() + 1)
			return;
		else if (position == 1)
			InsertBeg(data);
		else if (position == getCount() + 1)
			InsertEnd(data);
		else
		{
			LNode<T>* before = Head;		//pointer before the item inserted
			LNode<T>* after = Head;		//pointer after the item inserted
			LNode<T>* R = new LNode<T>(data);
			for (int i = 1; i < position--; i++)
				before = before->getNext();
			after = before->getNext();
			before->setNext(R);
			R->setNext(after);
			++count;
		}
	}


	void DeletePosition(int position)
	{
		if (Head == nullptr)
			return;
		else if (position < 1 || position > getCount())
			return;
		else if (position == 1)
		{
			LNode<T>* P = Head->getNext();
			delete Head;
			Head = P;
		}
		else if (position == getCount())
		{
			LNode<T>* ptr = Head;
			--position;
			for (int i = 1; i < position; i++)
				ptr = ptr->getNext();
			ptr->setNext(nullptr);
			--count;
		}
		else
		{
			LNode<T>* before = Head;        //pointer before the item inserted
			LNode<T>* deleted = Head;
			--position;
			for (int i = 1; i < position; i++)
				before = before->getNext();
			deleted = before->getNext();
			before->setNext(deleted->getNext());
			delete deleted;
			--count;
		}
	}

	bool deqHead(T& frntEntry)
	{
		if (isEmpty())
			return false;

		LNode<T>* nodeToDeletePtr = Head;
		frntEntry = Head->getItem();

		if (Head->getNext() == nullptr) {
			Head = nullptr;
		}
		else {
			Head = Head->getNext();
		}

		// Free memory reserved for the dequeued LNode
		delete nodeToDeletePtr;
		--count;
		return true;

	}

	bool isEmpty() {
		return (Head == nullptr);
	}

	LNode<T>* getHead()
	{
		return Head;
	}

	LNode<T>* getNodeAt(int position)
	{

		if (position < 1 || position > count)
			return nullptr;

		LNode<T>* curPtr = Head;
		for (int skip = 1; skip < position; skip++)
			curPtr = curPtr->getNext();

		return curPtr;
	}

	T getEntry(int position)
	{
		if ((position < 1) || (position > count))
		{
			return nullptr;
		}
		LNode<T>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();

	}

	bool remove(int pos)
	{
		if (!Head || pos > count || pos < 1)
			return 0;


		LNode<T>* curr = Head;
		if (pos == 1)
		{
			curr = Head;
			Head = Head->getNext();
		}

		else
		{
			LNode<T>* prev = getNodeAt(pos - 1);
			curr = prev->getNext();
			prev->setNext(curr->getNext());
		}

		curr->setNext(nullptr);
		delete curr;
		curr = nullptr;
		count--;
		return 1;
	}

};

#endif	