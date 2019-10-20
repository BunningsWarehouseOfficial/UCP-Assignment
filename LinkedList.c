/* Filename:           LinkedList.c
 * Author:             Kristian Rados (19764285)
 * Date Created:       02/10/2019
 * Date Last Modified: 20/10/2019
 * Purpose: All the necessary functions to implement a double-headed and 
            doubly-linked Linked List data structure that is properly generic.
            Taken from work done for UCP practical 7.                         */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

/* PURPOSE:
Creates the central Linked List struct from which the rest of the List extends
from and is allocated on the heap. */
LinkedList* createLinkedList()
{/* creating central list */
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL; /* initialising to empty */
    list->tail = NULL;
    return list;
}

/* PURPOSE:
Allocates a new node for the Linked List in the heap, assigns its associated
data and then inserts it to the start of the List as the new head. */
void insertStart(LinkedList* list, void* data)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->prev = NULL; /* if at start, prev is always NULL */
    newNode->data = data;

    /* first in list */
    if (list->head == NULL) 
    {
        newNode->next = NULL; /* creating node */
        list->head = newNode; /* connecting node */
        list->tail = newNode;
    }
    /* not first */
    else
    {
        newNode->next = list->head; /* creating node */
        list->head->prev = newNode; /* reconnecting next node */
        list->head = newNode;
    }
}

/* PURPOSE:
Retrieves the data stored inside the first node in the List (ie. the head) and
then removes the node from the list, disconnecting it and freeing its memory. */
void* removeStart(LinkedList* list)
{
    void* removed;
    LinkedListNode* head = list->head; /* temp pointer to first node */

    if (head == NULL)
    {
        removed = NULL;
    }
    /* 1 node only */
    else if (head->next == NULL)
    {
        removed = head->data; /* return data */
        list->head = NULL; /* disconnecting node */
        list->tail = NULL;
        free(head);
    }
    /* > 1 node */
    else
    {
        removed = head->data; /* return data */
        head->next->prev = NULL; /* disconnecting node */
        list->head = head->next; /* changing head */
        free(head);
    }
    return removed;
}

/* PURPOSE:
Allocates a new node for the Linked List in the heap, assigns its associated
data and then inserts it to the end of the List as the new tail. */
void insertLast(LinkedList* list, void* data)
{
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    newNode->next = NULL; /* if at end, next is always NULL */
    newNode->data = data;
     
    /* first in list */
    if (list->head == NULL) 
    {
        newNode->prev = NULL; /* creating node */
        list->head = newNode; /* connecting node */
        list->tail = newNode;
    }
    /* not first */
    else
    {
        newNode->prev = list->tail; /* creating node */
        list->tail->next = newNode; /* reconnecting previous node */
        list->tail = newNode;
    }
}

/* PURPOSE:
Retrieves the data stored inside the last node in the List (ie. the tail) and
then removes the node from the list, disconnecting it and freeing its memory. */
void* removeLast(LinkedList* list)
{
    void* removed;
    LinkedListNode* tail = list->tail; /* temp pointer to last node */

    /* list is empty */
    if (tail == NULL)
    {
        removed = NULL;
    }
    /* 1 node only */
    else if (tail->prev == NULL)
    {
        removed = tail->data; /* return data */
        list->head = NULL; /* disconnecting node */
        list->tail = NULL;
        free(tail);
    }
    /* > 1 node */
    else
    {
        removed = tail->data; /* return data */
        tail->prev->next = NULL; /* disconnecting node */
        list->tail = tail->prev; /* changing tail */
        free(tail);
    }
    return removed;
}

/* PURPOSE:
Iterates through each node in the List and uses an imported function pointer to
print the data stored within each node. Imported function allows for generic
printing of whatever data is stored within the List. */
void printLinkedList(LinkedList* list, PrintFn printNode)
{
    LinkedListNode* current = list->head; /* cursor for iterating through */
    while (current != NULL)
    {
        (*printNode)(current->data);
        current = current->next;
    }
}

/* PURPOSE:
Iterates through each node in the list and uses an imported function pointer to
free the memory for each node's data. After the data is freed, the node itself
is also freed. When all nodes in the List have been freed, the List itself is
free, hence 'deleting' the List. &free can imported for simple data. */
void freeLinkedList(LinkedList* list, FreeFn freeNode)
{
    LinkedListNode *node, *nextNode;

    node = list->head;
    while (node != NULL)
    {
        nextNode = node->next;
        (*freeNode)(node->data);
        free(node);
        node = nextNode;
    }
    free(list);
}