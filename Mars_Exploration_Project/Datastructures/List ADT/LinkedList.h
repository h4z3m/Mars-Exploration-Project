#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	LinkedList()
	{
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
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
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
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data)
	{
		Node<T>* ptr = Head;
		Node<T>* R = new Node<T>(data);
		for (int i = 1; i < getCount(); i++)
			ptr = ptr->getNext();
		ptr->setNext(R);
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
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
		Node<T>* current = Head;
		while (current != nullptr)
		{
			count++;
			current = current->getNext();
		}
		return count;
	}

	void InsertPosition(T data, int position)
	{
		if (Head == nullptr)
			return;
		else if (position < 1 || position > getCount() + 1)
			return;
		else if (position == 1)
			InsertBeg(data);
		else if (position == getCount()+1)
			InsertEnd(data);
		else
		{
			Node<T>* before = Head;		//pointer before the item inserted
			Node<T>* after = Head;		//pointer after the item inserted
			Node<T>* R = new Node<T>(data);
			for (int i = 1; i < position--; i++)
				before = before->getNext();
			after = before->getNext();
			before->setNext(R);
			R->setNext(after);
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
			Node<T>* P = Head->getNext();
			delete Head;
			Head = P;
		}
		else if (position == getCount())
		{
			Node<T>* ptr = Head;
			for (int i = 1; i < position--; i++)
				ptr = ptr->getNext();
			ptr->setNext(nullptr);
		}
		else
		{
			Node<T>* before = Head;		//pointer before the item inserted
			Node<T>* deleted = Head;
			for (int i = 1; i < position--; i++)
				before = before->getNext();
			deleted = before->getNext();
			before->setNext(deleted->getNext());
			delete deleted;
		}
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key);

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T &value);

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst();


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast();

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T &value);	

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value);	

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L);

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse();
		
};

#endif	
