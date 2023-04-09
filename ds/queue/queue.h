/* version 1.0 */
/*==============================================================================
Data Structures - Queue based on linked_list
Headetr
Dekel Sror
Review: Tzvi Cubac
Version 1
==============================================================================*/
#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h> /* size_t */

typedef struct queue_t queue_t;

/* Creates a new queue
   complexity - O(1)
   returns a handle to the queue */
queue_t *QCreate(void);

/* Destroys the queue pointed to by the given handle
   complexity - O(n)
   args:
    queue - the handle of the queue */
void QDestroy(queue_t *queue);

/* Inserts a new element to the
   last place of the queue
   complexity - O(1)
   args:
    queue - the handle of the queue
    data - the data to be inserted to the queue
        returns 0 if success, !0 if failed */
int QEnqueue(queue_t *queue, void *data);

/* Removes the first element from the queue
   complexity - O(1)
   args:\
    queue - the handle of the queue */
    /* TODO: what if queue is empty? */
void QDequeue(queue_t *queue);

/* Checks the size of the queue
   complexity - O(n)
   args:
    queue - the handle of the queue
        returns the number of elements in the queue */
size_t QSize(const queue_t *queue);

/* Checks if the queue is empty
   complexity - O(1)
   args:
    queue - the handle of the queue
        returns TRUE if empty, FALSE if not */
int QIsEmpty(const queue_t *queue);

/* Checks the value of the first element in the queue
   complexity - O(1)
   args:
    queue - the handle of the queue
        returns the data of the first element in the queue */
void *QPeek(const queue_t *queue);

/* Appends the src queue to the dest queue
   complexity - O(1)
   args:
    dest - queue to be appended to
    src - queue to be appended
        returns pointer to the new tail */
void QAppend(queue_t *dest, queue_t *src);

void QPrint(const queue_t *q);

#endif  /* QUEUE_H */
