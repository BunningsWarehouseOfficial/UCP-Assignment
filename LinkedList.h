#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* PURPOSE:  */
typedef struct LinkedListNode
{
    void* data;
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
} LinkedListNode;

/* PURPOSE:  */
typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

LinkedList* createLinkedList();

void insertStart(LinkedList* list, void* data);
void* removeStart(LinkedList* list);

void insertLast(LinkedList* list, void* data);
void* removeLast(LinkedList* list);

void printLinkedList(LinkedList* list, void (*print)(void*));
void freeLinkedList(LinkedList* list);
/*void freeLinkedList(LinkedList* list, void (*print)(void*));*/
/*void freeNode(LinkedListNode* node, void (*print)(void*));*/

#endif
