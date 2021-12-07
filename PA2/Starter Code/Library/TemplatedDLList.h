// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e=T(), DLListNode *p=nullptr, DLListNode *n=nullptr): obj(e), prev(p), next(n) {}
};

// doubly linked list class
template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList();// default constructor
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

// output operator
template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll);


#endif

// implementation of the DLList class

template <typename T>
DLList<T>::DLList() {
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T>::DLList(const DLList<T>& dll) { // copy constructor
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode<T> *newNode = dll.header.next;
    while ( newNode != &dll.trailer ) {
        insert_last( newNode->obj );
        newNode = newNode->next;
    }
}

template <typename T>
DLList<T>::DLList(DLList&& dll) { // move constructor
    header.next = &trailer;
    trailer.prev = &header;
    
    if ( !dll.is_empty() ) {
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        header.next->prev = &header;
        trailer.prev->next = &trailer;
        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
}

template <typename T>
DLList<T>::~DLList() { // destructor
    DLListNode<T> *lastNode, *curNode = header.next;
    while ( curNode != &trailer ) {
        lastNode = curNode;
        curNode = curNode->next;
        delete lastNode;
    }
    
    header.next = &trailer;
    trailer.prev = &header;
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& dll) { // copy assignment operator
    DLListNode<T> *lastNode, *curNode = header.next;
    while ( curNode != &trailer ) {
        lastNode = curNode;
        curNode = curNode->next;
        delete lastNode;
    }
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode<T> *newNode = dll.header.next;
    while ( newNode != &dll.trailer ) {
        insert_last( newNode->obj );
        newNode = newNode->next;
    }
    
    return *this;
}

template <typename T>
DLList<T>& DLList<T>::operator=(DLList<T>&& dll) { // move assignment operator
    DLListNode<T> *lastNode, *curNode = header.next;
    while ( curNode != &trailer ) {
        lastNode = curNode;
        curNode = curNode->next;
        delete lastNode;
    }
    header.next = &trailer;
    trailer.prev = &header;
    
    if ( !dll.is_empty() ) {
        header.next = dll.header.next;
        trailer.prev = dll.trailer.prev;
        header.next->prev = &header;
        trailer.prev->next = &trailer;
        dll.header.next = &dll.trailer;
        dll.trailer.prev = &dll.header;
    }
    
    return *this;
}

template <typename T>
T DLList<T>::first() const { // return the first object
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    return header.next->obj;
}

template <typename T>
T DLList<T>::last() const { // return the last object
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    return trailer.prev->obj;
}

template <typename T>
void DLList<T>::insert_first(T obj) { // insert to the first node
    DLListNode<T> *node = new DLListNode<T>(obj, &header, header.next);
    header.next->prev = node;
    header.next = node;
}

template <typename T>
T DLList<T>::remove_first() { // remove the first node
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    
    DLListNode<T> *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    
    T obj = node->obj;
    delete node;
    return obj;
}

template <typename T>
void DLList<T>::insert_last(T obj) { // insert to the last node
    DLListNode<T> *node = new DLListNode<T>(obj, trailer.prev, &trailer);
    
    trailer.prev->next = node;
    trailer.prev = node;
}

template <typename T>
T DLList<T>::remove_last() { // remove the last node
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    
    DLListNode<T> *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    
    T obj = node->obj;
    delete node;
    return obj;
}

template <typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj) {
    DLListNode<T> *node = new DLListNode<T>(obj, &p, p.next);
    p.next->prev = node;
    p.next = node;
}

template <typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj) {
    DLListNode<T> *node = new DLListNode<T>(obj, p.prev, &p);
    p.prev->next = node;
    p.prev = node;
}

template <typename T>
T DLList<T>::remove_after(DLListNode<T> &p) {
    if ( is_empty() == true or p.next == &trailer ) throw ("Empty Doubly Linked List");
    DLListNode<T> *nodeDelete = p.next;
    p.next = nodeDelete->next;
    nodeDelete->next->prev = &p;
    T obj = nodeDelete->obj;
    delete nodeDelete;
    return obj;
}

template <typename T>
T DLList<T>::remove_before(DLListNode<T> &p) {
    if ( is_empty() == true or p.prev == &header ) throw ("Empty Doubly Linked List");
    DLListNode<T> *nodeDelete = p.prev;
    p.prev = nodeDelete->prev;
    nodeDelete->prev->next = &p;
    T obj = nodeDelete->obj;
    delete nodeDelete;
    return obj;
}

template <typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll) {
    DLListNode<T> *curNode = dll.first_node();
    while ( curNode != dll.after_last_node() ) {
        out << curNode->obj << ", ";
        curNode = curNode->next;
    }
    return out;
}
