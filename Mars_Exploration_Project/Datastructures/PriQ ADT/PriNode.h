
#ifndef _PNODE
#define _PNODE
template < typename T>
class PriNode
{
private :
	T item; // A data item
	int priority; // an item priority
	PriNode<T>* next; // Pointer to next node
public :
	PriNode();
	PriNode( const T & r_Item, int p =-1);	
	PriNode( const T & r_Item, PriNode<T>* nextNodePtr);
	void setItem( const T & r_Item);
	void setPrio(const int& r_Prio);
	void setNext(PriNode<T>* nextNodePtr);
	T getItem() const ;
	int getPrio() const
	{
		return priority;
	}
	PriNode<T>* getNext() const ;
}; // end Node
#endif

template < typename T>
PriNode<T>::PriNode() 
{
	priority = -1;
	next = nullptr;
} 

template < typename T>
PriNode<T>::PriNode( const T& r_Item, int p)
{
	item = r_Item;
	next = nullptr;
	priority = p;
} 

template < typename T>
PriNode<T>::PriNode( const T& r_Item, PriNode<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template < typename T>
void PriNode<T>::setItem( const T& r_Item)
{
	item = r_Item;
} 

template < typename T>
void PriNode<T>::setPrio(const int& r_Prio)
{
	priority = r_Prio;
}

template < typename T>
void PriNode<T>::setNext(PriNode<T>* nextNodePtr)
{
	next = nextNodePtr;
} 

template < typename T>
T PriNode<T>::getItem() const
{
	return item;
} 


template < typename T>
PriNode<T>* PriNode<T>::getNext() const
{
	return next;
} 