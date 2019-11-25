#ifndef LINKEDLIST
#define LINKEDLIST
#include <iostream>
using namespace std;

#include "LListIter.h"

// Need to prototype template classes 
// since they are referenced as friends below
template <typename T> class LListIter;

/////////////////////////////////////////////////////
// define a class to contain one linked list Node
template <typename T> 
class Node {  
  private:
    Node(T value=T(), Node* ptr=NULL) {
      data= value; next= ptr;
    }

    T getData() { return data; }
    void setData(const T& d) { data= d; }
    Node *getNext() { return next; }

    T data;
    Node *next;

    // must make LinkedList and LListIter friends to Node
    // otherwise, Node pointers will need to be passed around
    // allowing visiblity into LL elements
    friend class LinkedList<T>;
    friend class LListIter<T>;
};

/////////////////////////////////////////////////////
// the linked list class
template <typename T> 
class LinkedList {
  public:
    // Default constructor
    LinkedList();
    // destructor
    ~LinkedList();

    // add an item to the end
    void add(T); 
    // remove item with specified value
    bool remove(T);
    // delete everything
    void deleteAll();
    // replace an existing entry with given item
    bool replace(T);

    // Is the LinkedList empty?
    bool isEmpty();
    // find the max value in the list
    T findMax();
    // sort the list in ascending order
    void sortAscend();
    // find the min value in the list
    T findMin();
    // sort the list in descending order
    void sortDescend();
    // reverse the order of items in the list 
    void reverse();

    // get a copy of an entry
    T getEntry(T);

  private:
    // look for an item in the list
    Node<T>* findItem(T);

    // linked list pointer
    Node<T>* first;

    // extract item with specified value
    // return the extracted node
    Node<T>* extract(T);

    // make iterator a friend
    friend class LListIter<T>;
};
 
// Output a linked list, using a list iterator
template <typename T> 
ostream& operator<<(ostream &os,const LinkedList<T> &llist) {  
  LListIter<T>  iter(llist);
  if(!iter.end()) { 
    do {
      os << " " << *iter;
    } while(iter.next());
  }
  return os;
}

/////////////////////////////////////////////////////
// Linked List Implementations
/////////////////////////////////////////////////////

// Construct empty LinkedList
template <typename T> 
LinkedList<T>::LinkedList() {
  first= NULL;
}

// Free all Nodes
template <typename T> 
LinkedList<T>::~LinkedList() {
  deleteAll();
}

// is list empty?
// Note: inline !!!!!!!!!!!!
template <typename T> inline 
bool LinkedList<T>::isEmpty() {
  return (first == NULL);
}

// remove an item from the llist 
// return true if successful (false if not found)
template <typename T> 
bool LinkedList<T>::remove(T val) {  
  Node<T> *current= first;
  if(!isEmpty()) {
    // val is first item, remove it
    if(val == current->data) {
      first= current->next; delete current;
      return true;
    }
    // not the first, check the rest
    while(current->next != NULL) {
      if(val == current->next->data) {
        Node<T> *temp= current->next->next;
        delete current->next; current->next= temp;
        return true;
      }
      // not found, go on to the next one
      current= current->next;
    }
  }
  return false;
}

// Delete all Nodes in the linked list
template <typename T> 
void LinkedList<T>::deleteAll() {  
  Node<T> *ptr= first;
  while (ptr != NULL) {  
    Node<T> *doomed = ptr;
    ptr = ptr->next;
    delete doomed;
  }
}

// locate and return a copy of an item
template <typename T> 
T LinkedList<T>::getEntry(T val) {  
  Node<T> *ptr = first;
  while(ptr != NULL) {
    if(ptr->data == val) { 
       return ptr->getData(); 
    }
    ptr = ptr->next; 
  }
  return T();
}

// sort the linked list in ascending order
template <class T>
void LinkedList<T>::sortAscend() {
  Node<T> *nptr= NULL;
  Node<T> *lptr= nptr;

  while(!isEmpty()) {
    T data= findMax();
    lptr= nptr; nptr= extract(data); nptr->next= lptr;
  }
  first= nptr;
}

/////////////////////////////////////////////////////
//
// COMPLETE THE FOLLOWING METHODS !!!
//
/////////////////////////////////////////////////////

// Add an new item to the end of the list
template <typename T> 
void LinkedList<T>::add(T val) {
	if (isEmpty()) //is the list empty?
	{//if so, set the first pointer to a new node
		first = new Node<T>(val, first);
	}
	else
	{//otherwise, create a new node after the last node
		Node<T>* current = first;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new Node<T>(val, current->next);
	}
}

// Replace the existing item that matches the supplied
// item with the supplied item
// return true if successful, false otherwise
template <typename T> 
bool LinkedList<T>::replace(T nitem) 
{
	Node<T>* ptr = first;
	while (ptr != NULL)
	{
		if (ptr->data == nitem)
		{
			ptr->data = nitem;
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}

// extract an item from the llist 
// return pointer to the extracted item if successful 
// do NOT delete the extracted item!!!
// return NULL if not found
template <typename T> 
Node<T> *LinkedList<T>::extract(T val)
{
	Node<T>* current = first;
	if (current == NULL)
	{
		return NULL;
	}

	else
	{
		while (current != NULL)
		{
			if (val == current->data)
				return current;
			else
				current = current->next;
		}
		if (current == NULL)
			return NULL;
	}
}

// get the max value in the list
// assumes the list is not empty
// if it is, return the default value for T
template <typename T>
T LinkedList<T>::findMax() 
{
	if (isEmpty())
		return T();

	T *max = first->data;
	while (max != NULL)
	{
		if (max.getName() < (max->next).getName())
		{
			max = max->next;
		}
		if (max.getName() > (max->next).getName())
		{
			if (max->next != NULL)
			{
				
			}
		}
	}
	//max is now an employee object
	//compare two employee objects
	//if Joe > max, make max = Joe.

  return T(); // REPLACE THIS!!!
}

// reverse the item order
template <class T>
void LinkedList<T>::reverse() {
}

// get the min value in the list
// assumes the list is not empty
// if it is, return the default value for T
template <typename T>
T LinkedList<T>::findMin() {
  return T(); // REPLACE THIS!!!
}

// sort the linked list in ascending order
template <class T>
void LinkedList<T>::sortDescend() {
}

#endif
