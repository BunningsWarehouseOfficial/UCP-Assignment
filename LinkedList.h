#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* PURPOSE:
Defining a struct that acts as a node in a Linked List. Stores a pointer to the
previous node in the list, a pointer to the next node in the list and a generic
void pointer to whatever data is being stored in the node. */
typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

/* PURPOSE:
Defining a struct that acts as the central Linked List struct from which the
rest of the List extends from. Stores a pointer the head of the list (ie. the
first node) and stores a pointer to the tail of the list (ie. the last node). */
typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

/* PURPOSE:
Defining a function pointer type that is used in printLinkedList where it is
imported to provide the ability to print generic data from the List node */
typedef void (*PrintFn)(void*);

/* PURPOSE:
Defining a function pointer type that is used in freeLinkedList where it is
imported to provide the ability to free complex data types that need more than
just a simple free() */
typedef void (*FreeFn)(void*);

LinkedList* createLinkedList();

void insertStart(LinkedList* list, void* data);
void* removeStart(LinkedList* list);

void insertLast(LinkedList* list, void* data);
void* removeLast(LinkedList* list);

void printLinkedList(LinkedList* list, void (*print)(void*));
void freeLinkedList(LinkedList* list, FreeFn freeNode);

#endif
