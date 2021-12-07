// implementation of the DLList class

#include "DLList.h"

DLList::DLList() {
    header.next = &trailer;
    trailer.prev = &header;
}

DLList::DLList(const DLList& dll) { // copy constructor
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode *newNode = dll.header.next;
    while ( newNode != &dll.trailer ) {
        insert_last( newNode->obj );
        newNode = newNode->next;
    }
}

DLList::DLList(DLList&& dll) { // move constructor
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

DLList::~DLList() { // destructor
    DLListNode *lastNode, *curNode = header.next;
    while ( curNode != &trailer ) {
        lastNode = curNode;
        curNode = curNode->next;
        delete lastNode;
    }
    
    header.next = &trailer;
    trailer.prev = &header;
}

DLList& DLList::operator=(const DLList& dll) { // copy assignment operator
    DLListNode *lastNode, *curNode = header.next;
    while ( curNode != &trailer ) {
        lastNode = curNode;
        curNode = curNode->next;
        delete lastNode;
    }
    header.next = &trailer;
    trailer.prev = &header;
    
    DLListNode *newNode = dll.header.next;
    while ( newNode != &dll.trailer ) {
        insert_last( newNode->obj );
        newNode = newNode->next;
    }
    
    return *this;
}

DLList& DLList::operator=(DLList&& dll) { // move assignment operator
    DLListNode *lastNode, *curNode = header.next;
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

DLListNode* DLList::first_node() const { // return the pointer to the first node (header's next)
    return header.next;
}

const DLListNode* DLList::after_last_node() const { // return the pointer to the trailer
    return &trailer;
}

bool DLList::is_empty() const { // return if the list is empty
    return header.next == &trailer;
}
int DLList::first() const { // return the first object
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    return header.next->obj;
}

int DLList::last() const { // return the last object
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    return trailer.prev->obj;
}

void DLList::insert_first(int obj) { // insert to the first node
    DLListNode *node = new DLListNode(obj, &header, header.next);
    header.next->prev = node;
    header.next = node;
}

int DLList::remove_first() { // remove the first node
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    
    DLListNode *node = header.next;
    node->next->prev = &header;
    header.next = node->next;
    
    int obj = node->obj;
    delete node;
    return obj;
}

void DLList::insert_last(int obj) { // insert to the last node
    DLListNode *node = new DLListNode(obj, trailer.prev, &trailer);
    
    trailer.prev->next = node;
    trailer.prev = node;
}

int DLList::remove_last() { // remove the last node
    if ( is_empty() ) throw ("Empty Doubly Linked List");
    
    DLListNode *node = trailer.prev;
    node->prev->next = &trailer;
    trailer.prev = node->prev;
    
    int obj = node->obj;
    delete node;
    return obj;
}

void DLList::insert_after(DLListNode &p, int obj) {
    DLListNode *node = new DLListNode(obj, &p, p.next);
    p.next->prev = node;
    p.next = node;
}

void DLList::insert_before(DLListNode &p, int obj) {
    DLListNode *node = new DLListNode(obj, p.prev, &p);
    p.prev->next = node;
    p.prev = node;
}

int DLList::remove_after(DLListNode &p) {
    if ( is_empty() or p.next == &trailer ) throw ("Empty Doubly Linked List");
    DLListNode *nodeDelete = p.next;
    p.next = nodeDelete->next;
    nodeDelete->next->prev = &p;
    int obj = nodeDelete->obj;
    delete nodeDelete;
    return obj;
}

int DLList::remove_before(DLListNode &p) {
    if ( is_empty() or p.prev == &header ) throw ("Empty Doubly Linked List");
    DLListNode *nodeDelete = p.prev;
    p.prev = nodeDelete->prev;
    nodeDelete->prev->next = &p;
    int obj = nodeDelete->obj;
    delete nodeDelete;
    return obj;
}

ostream& operator<<(ostream& out, const DLList& dll) {
    DLListNode *curNode = dll.first_node();
    while ( curNode != dll.after_last_node() ) {
        out << curNode->obj << ", ";
        curNode = curNode->next;
    }
    return out;
}
