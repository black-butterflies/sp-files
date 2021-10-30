#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// ! SEG FAULT!
/*
 * implementation of a FIFO queue using a linked list
 * ignore priority argument in add()
 */

struct q_element
{
    struct q_element *next;
    void *value;
};

struct queue
{
    struct q_element *head;
    struct q_element *tail;
};

/*
 * create a Queue that holds Items
 * returns NULL if the create call failed (malloc failure)
 */
Queue *q_create(void)
{
    struct queue *p;

    if ((p = (struct queue *)malloc(sizeof(struct queue))) != NULL)
    {
        p->head = NULL;
        p->tail = NULL;
    }
    return p;
}

/*
 * add Item to the Queue; 3rd arg is priority in MIN_PRIO..MAX_PRIO;
 * return 1/0 if successful/not-successful
 */
int q_add(Queue *q, Item i, int prio)
{
    struct q_element *p;

    p = (struct q_element *)malloc(sizeof(struct q_element));
    if (p != NULL)
    {
        p->value = i;
        p->next = NULL;
        if (q->head == NULL)
            q->head = p;
        else
            q->tail->next = p;
        q->tail = p;
        return 1;
    }
    return 0;
}

/*
 * remove next Item from queue; returns NULL if queue is empty
 */
Item q_remove(Queue *q)
{
    if (q->tail == NULL)
    {
        puts("Empty list");
        // the list is empty
        return NULL;
    }

    struct q_element *cursor, *p;
    cursor = q->head;
    while (cursor->next != NULL && cursor->next != q->tail)
    {
        puts("checking cursor");
        // move the cursor to the element before the tail
        cursor = cursor->next;
    }
    puts("cursor");
    if (cursor->next == NULL)
    {
        // the list only has one element
        q->head = NULL;
    }
    p = q->tail;
    // the cursor will become the tail
    cursor->next = NULL;
    q->tail = cursor;

    Item i = p->value;
    free(p);

    return i;
}
