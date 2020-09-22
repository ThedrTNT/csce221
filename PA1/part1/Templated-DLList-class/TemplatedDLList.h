// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>

using namespace std;

// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// doubly linked list node
template<typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p = nullptr, DLListNode *n = nullptr)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list class
template<typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList() : header(T()), trailer(T()) // default constructor
  { header.next = &trailer; trailer.prev = &header; }
  DLList(const DLList<T>& dll); // copy constructor
  DLList(DLList<T>&& dll); // move constructor
  ~DLList(); // destructor
  DLList<T>& operator=(const DLList<T>& dll); // copy assignment operator
  DLList<T>& operator=(DLList<T>&& dll); // move assignment operator
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insert_first(T obj); // insert to the first node
  T remove_first(); // remove the first node
  void insert_last(T obj); // insert to the last node
  T remove_last(); // remove the last node
  void insert_after(DLListNode<T> &p, T obj);
  void insert_before(DLListNode<T> &p, T obj);
  T remove_after(DLListNode<T> &p);
  T remove_before(DLListNode<T> &p);
};

// copy constructor
//O(n)
template<typename T>
DLList<T>::DLList(const DLList<T>& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  /* Complete this function */
  DLListNode<T>* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    insert_last(curr->obj);
    curr = curr->next;
  }

}
// move constructor
//O(1)
template<typename T>
DLList<T>::DLList(DLList<T>&& dll)
{
  /* Complete this function */

  //what the fuck is this

  header.next = dll.header.next;
  trailer.prev = dll.trailer.prev;

  header.next->prev = &header;
  trailer.prev->next = &trailer;

  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;
}

// copy assignment operator
//O(n)
template<typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll)
{
  /* Complete this function */
  DLListNode<T>* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode<T>* del = curr;
    curr = curr->next;
    delete del;
  }

  header.next = &trailer;
  trailer.prev = &header;

  curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    insert_last(curr->obj);
    curr = curr->next;
  }

  return *this;
}

// move assignment operator
//O(n)
template<typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll)
{
  /* Complete this function */

  //what the fuck is this

  DLListNode<T>* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode<T>* del = curr;
    curr = curr->next;
    delete del;
  }

  header.next = dll.header.next;
  trailer.prev = dll.trailer.prev;

  header.next->prev = &header;
  trailer.prev->next = &trailer;

  dll.header.next = &dll.trailer;
  dll.trailer.prev = &dll.header;

  return *this;
}

// destructor
//O(n)
template<typename T>
DLList<T>::~DLList()
{
  /* Complete this function */
  DLListNode<T>* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode<T>* del = curr;
    curr = curr->next;
    delete del;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new object as the first one
//O(1)
template<typename T>
void DLList<T>::insert_first(T obj)
{ 
  /* Complete this function */
  DLListNode<T>* newNode = new DLListNode<T>(obj, &header, header.next);
  if (is_empty()) {
    //std::cout << "test" << std::endl;
    header.next = newNode;
    trailer.prev = newNode;
    return;
  }
  header.next->prev = newNode;
  header.next = newNode;
}

// insert a new object as the last one
//O(1)
template<typename T>
void DLList<T>::insert_last(T obj)
{
  /* Complete this function */
  DLListNode<T>* newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
  if (is_empty()) {
    //std::cout << "test" << std::endl;
    header.next = newNode;
    trailer.prev = newNode;
    return;
  }
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first node from the list
//O(1)
template<typename T>
T DLList<T>::remove_first()
{ 
  /* Complete this function */
  if (is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
    return 0;
  }

  if (header.next == trailer.prev) {
    DLListNode<T>* delNode = header.next;
    header.next = delNode->next;
    delNode->next->prev = &header;
    T retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode<T>* delNode = header.next;
  header.next = delNode->next;
  delNode->next->prev = &header;
  T retVal = delNode->obj;
  delete delNode;
  delNode = nullptr;
  return retVal;
}

// remove the last node from the list
//O(1)
template<typename T>
T DLList<T>::remove_last()
{
  /* Complete this function */
  if (is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
    return 0;
  }

  if (header.next == trailer.prev) {
    DLListNode<T>* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    T retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode<T>* delNode = trailer.prev;
  delNode->prev->next = &trailer;
  trailer.prev = delNode->prev;
  T retVal = delNode->obj;
  delete delNode;
  delNode = nullptr;
  return retVal;
}

// return the first object (do not remove)
//O(1)
template<typename T>
T DLList<T>::first() const
{ 
  /* Complete this function */
  return header.next->obj;
}

// return the last object (do not remove)
//O(1)
template<typename T>
T DLList<T>::last() const
{
  /* Complete this function */
  return trailer.prev->obj;
}

// insert a new node after the node p
//O(1)
template<typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  /* Complete this function */
  DLListNode<T>* newNode = new DLListNode<T>(obj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;
}

// insert a new node before the node p
//O(1)
template<typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
  /* Complete this function */
  DLListNode<T>* newNode = new DLListNode<T>(obj, p.prev, &p);
  p.prev->next = newNode;
  p.prev = newNode;
}

// remove the node after the node p
//O(1)
template<typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
  /* Complete this function */
  if (header.next == trailer.prev) {
    DLListNode<T>* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    T retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode<T>* delNode = p.next;
  p.next = delNode->next;
  delNode->next->prev = &p;
  T retVal = delNode->obj;
  delete delNode;

  return retVal;
}

// remove the node before the node p
//O(1)
template<typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
  /* Complete this function */
  if (header.next == trailer.prev) {
    DLListNode<T>* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    T retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode<T>* delNode = p.prev;
  p.prev = delNode->prev;
  delNode->prev->next = &p;
  T retVal = delNode->obj;
  delete delNode;

  return retVal;
}

// output operator
//O(n)
template<typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll)
{  
  /* Complete this function */
  DLListNode<T>* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    out << curr->obj << ", ";
    curr = curr->next;
  }

  return out;
}


#endif
