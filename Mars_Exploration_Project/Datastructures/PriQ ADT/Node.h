
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
private :
	T item; // A data item
	int priority; // an item priority
	Node<T>* next; // Pointer to next node
public :
	Node();
	Node( const T & r_Item, int p =-1);	
	Node( const T & r_Item, Node<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setPrio(const T& r_Prio);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const ;
	int getPrio() const
	{
		return priority;
	}
	Node<T>* getNext() const ;
}; // end Node
#endif

template < typename T>
Node<T>::Node() 
{
	priority = -1;
	next = nullptr;
} 

template < typename T>
Node<T>::Node( const T& r_Item, int p)
{
	item = r_Item;
	next = nullptr;
	priority = p;
} 

template < typename T>
Node<T>::Node( const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void Node<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void Node<T>::setPrio(const T& r_Prio)
{
	priority = r_Prio;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T Node<T>::getItem() const
{
	return item;
} 

//template < typename T>
//T Node<T>::getPrio() const
//{
//	return priority;
//}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
} 