#ifndef _LLNode
#define _LLNode
//First let's declare a single LNode in the list
template<typename T>
class LNode
{
private :
	T item;	// A data item (can be any complex sturcture)
	LNode<T>* next;	// Pointer to next LNode
public :

	LNode( ) //default constructor
	{
		next= nullptr;
	} 

	LNode( T newItem) //non-default constructor
	{
		item = newItem;
		next= nullptr;

	}

	void setItem( T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(LNode<T>* nextLNodePtr)
	{
	next = nextLNodePtr;
	} // end setNext

	T getItem() const
	{
		return item;
	} // end getItem

	LNode<T>* getNext() const
	{
		return next;
	}
}; // end LNode

#endif	
