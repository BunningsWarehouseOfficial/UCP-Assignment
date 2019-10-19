/* Filename:           LinkedList.c
 * Author:             Kristian Rados (19764285)
 * Date Created:       02/10/2019
 * Date Last Modified: 19/10/2019
 * Purpose: __________________________________________________________________*/

#include <stdlib.h>
#include <stdio.h> /*** Is this needed? ***/
#include "LinkedList.h"

/* PURPOSE:  */
LinkedList* createLinkedList()
{/* creating central list */
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL; /* initialising to empty */
    list->tail = NULL;
    return list;
}

/* PURPOSE:  */
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

/* PURPOSE:  */
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

/* PURPOSE:  */
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

/* PURPOSE:  */
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

/* PURPOSE:  */
void printLinkedList(LinkedList* list, void (*print)(void*))
{
    LinkedListNode* current = list->head; /* cursor for iterating through */
    while (current != NULL)
    {
        (*print)(current->data);
        current = current->next;
    }
}

/* PURPOSE:  */
void freeLinkedList(LinkedList* list, FreeFn freeNode)
{
    LinkedListNode *current;

    current = list->head;
    while (current != NULL)
    {
        (*freeNode)(current->data);
        free(current);
        current = current->next;
    }
    free(list);
}