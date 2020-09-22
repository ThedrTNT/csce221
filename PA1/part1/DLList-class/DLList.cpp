// implementation of the DLList class

#include <stdexcept>
#include <iostream>
#include "DLList.h"


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
//O(n)
DLList::DLList(const DLList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;
  
  /* Complete this function */
  DLListNode* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    insert_last(curr->obj);
    curr = curr->next;
  }

}
// move constructor
//O(1)
DLList::DLList(DLList&& dll)
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
DLList& DLList::operator=(const DLList& dll)
{
  /* Complete this function */
  DLListNode* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode* del = curr;
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
DLList& DLList::operator=(DLList&& dll)
{
  /* Complete this function */

  //what the fuck is this

  DLListNode* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode* del = curr;
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
DLList::~DLList()
{
  /* Complete this function */
  DLListNode* curr = first_node();
  while (curr != after_last_node()) {
    DLListNode* del = curr;
    curr = curr->next;
    delete del;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new object as the first one
//O(1)
void DLList::insert_first(int obj)
{ 
  /* Complete this function */
  DLListNode* newNode = new DLListNode(obj, &header, header.next);
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
void DLList::insert_last(int obj)
{
  /* Complete this function */
  DLListNode* newNode = new DLListNode(obj, trailer.prev, &trailer);
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
int DLList::remove_first()
{ 
  /* Complete this function */
  if (is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
    return 0;
  }

  if (header.next == trailer.prev) {
    DLListNode* delNode = header.next;
    header.next = delNode->next;
    delNode->next->prev = &header;
    int retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode* delNode = header.next;
  header.next = delNode->next;
  delNode->next->prev = &header;
  int retVal = delNode->obj;
  delete delNode;
  delNode = nullptr;
  return retVal;
}

// remove the last node from the list
//O(1)
int DLList::remove_last()
{
  /* Complete this function */
  if (is_empty()) {
    header.next = &trailer;
    trailer.prev = &header;
    return 0;
  }

  if (header.next == trailer.prev) {
    DLListNode* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    int retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode* delNode = trailer.prev;
  delNode->prev->next = &trailer;
  trailer.prev = delNode->prev;
  int retVal = delNode->obj;
  delete delNode;
  delNode = nullptr;
  return retVal;
}

// return the first object (do not remove)
//O(1)
int DLList::first() const
{ 
  /* Complete this function */
  return header.next->obj;
}

// return the last object (do not remove)
//O(1)
int DLList::last() const
{
  /* Complete this function */
  return trailer.prev->obj;
}

// insert a new node after the node p
//O(1)
void DLList::insert_after(DLListNode &p, int obj)
{
  /* Complete this function */
  DLListNode* newNode = new DLListNode(obj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;
}

// insert a new node before the node p
//O(1)
void DLList::insert_before(DLListNode &p, int obj)
{
  /* Complete this function */
  DLListNode* newNode = new DLListNode(obj, p.prev, &p);
  p.prev->next = newNode;
  p.prev = newNode;
}

// remove the node after the node p
//O(1)
int DLList::remove_after(DLListNode &p)
{
  /* Complete this function */
  if (header.next == trailer.prev) {
    DLListNode* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    int retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode* delNode = p.next;
  p.next = delNode->next;
  delNode->next->prev = &p;
  int retVal = delNode->obj;
  delete delNode;

  return retVal;
}

// remove the node before the node p
//O(1)
int DLList::remove_before(DLListNode &p)
{
  /* Complete this function */
  if (header.next == trailer.prev) {
    DLListNode* delNode = trailer.prev;
    delNode->prev->next = &trailer;
    trailer.prev = delNode->prev;
    int retVal = delNode->obj;
    delete delNode;
    delNode = nullptr;
    header.next = &trailer;
    trailer.prev = &header;
    return retVal;
  }

  DLListNode* delNode = p.prev;
  p.prev = delNode->prev;
  delNode->prev->next = &p;
  int retVal = delNode->obj;
  delete delNode;

  return retVal;
}

// output operator
//O(n)
ostream& operator<<(ostream& out, const DLList& dll)
{  
  /* Complete this function */
  DLListNode* curr = dll.first_node();
  while (curr != dll.after_last_node()) {
    out << curr->obj << ", ";
    curr = curr->next;
  }

  return out;
}
