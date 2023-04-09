/*==============================================================================
Data Structures - Doubly Linked List with iterators
Header
Dekel Sror
Review: Moti Zamir
OL66
Version 1
==============================================================================*/
#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stddef.h> /* size_t */

typedef struct dlist_s dlist_t;

typedef struct diter_s
{
    void *info;
} diter_t;

/* Iterator functions: */
/*  DLBegin
	Returns an iterator to first element in the list.

	Arguments:
		list.

	complexity O(1)
*/
diter_t DLBegin(const dlist_t *list);

/*  DLEnd
	Returns an iterator to the end of the list.
	not a valid location.

	Arguments:
		list.

	complexity O(1)
*/
diter_t DLEnd(const dlist_t *list);

/* DLNext
	Increase a given iterator to the next position.
 	If iter is End, behaviour is undefined.

	Arguments:
		iter.

 	complexity O(1)
*/
diter_t DLNext(diter_t iter);

/*  DLPrev
	Decrease a given iterator to the previous position.
  	If iter is Start, behaviour is undefined.

	Arguments:
		iter.

  	complexity O(1)
*/
diter_t DLPrev(diter_t iter);

/* DLIsSameIter
	Given two iterators, returns true if equal, false otherwise.

	Arguments:
		iter1.
		iter2.

	complexity O(1)
*/
int DLIsSameIter(const diter_t iter1, const diter_t iter2);

/*  DLGetData
	returns pointer to data of a given iterator.

	Arguments:
		iter1.
		iter2.

	for invalid iterator, behaviour is undefined.

	complexity O(1)
*/
void *DLGetData(diter_t iter);

/*---------------------------------------------------------------------------*/
/* DList functions: */

/* DLCreate
	Creates a new list.

	returns list pointer, NULL on failure.

	complexity O(1)
*/
dlist_t *DLCreate(void);

/*  DLDestroy
	Destroy a given list.

	arguments:
		list.

	complexity O(n)
*/
void DLDestroy(dlist_t *list);

/*  DLCount
	Count number elements in a given list.

	arguments:
		list.

	returns number of elements.

	complexity O(n)
*/
size_t DLCount(const dlist_t *list);

/*  DLIsEmpty
	For a given list, return true if empty,
	false otherwise.

	arguments:
		list.

	complexity O(1)
*/
int DLIsEmpty(const dlist_t *list);

/*  DLInsert
	Insert a new element before a given iterator

	arguments:
    list - the list it belongs to, to return End in case of failure
		iterator - to insert before.
		data - pointer to the data to be inserted.

	returns iterator of the new elements,
	returns iter End of list on failure.

	complexity O(1)
*/
diter_t DLInsert(dlist_t *list, diter_t iter, void *data);

/*  DLInsertAfter
	Insert a new element after a given iterator

	arguments:
        list - the list to insert to, function returns End of lists
            in case of failure.
		iterator - to insert after.
		data - pointer to the data to be inserted.

	returns iterator of the new elements,
	returns iter End of list on failure.

	complexity O(1)
*/
diter_t DLInsertAfter(dlist_t *list, diter_t iter, void *data);

/*  DLErase
	Remove a given element from the list

	arguments:
		iterator - to the element to be removed.

	complexity O(1)
*/
void DLErase(diter_t iter);

/*  DLPushFront
	Insert a new element to the first position in a given list

	arguments:
		list.
		data - pointer to the data to be inserted.

	returns the new iterator on success, End of list on failure

	complexity O(1)
*/
diter_t DLPushFront(dlist_t *list, void *data);

/*  DLPushBack
	Insert a new element to the last position in a given list

	arguments:
		list.
		data - pointer to the data to be inserted.

	returns the new iterator on success, End of list on failure

	complexity O(1)
*/
diter_t DLPushBack(dlist_t *list, void *data);

/*  DLPopFront
	remove the first element in the given list

	arguments:
		list.

	For an empty list, behaviour is undefined

	complexity O(1)
*/
void DLPopFront(dlist_t *list);

/*  DLPopBack
	remove the last element in the given list

	arguments:
		list.

	For an empty list, behaiviour is undefined

	complexity O(1)
*/
void DLPopBack(dlist_t *list);

/*  DLForEach
	Performs a given operation for each member between two given itearatos

	arguments:
		start - member to start from.
		end - operate until this member (not included).
		operation_func - the operation to perform.
		arg - the argument for the operation

	returns 0 on success, appropriate error code otherwise

	complexity O(n)
*/
int DLForEach(
      diter_t from
    , diter_t to
    , int (*operation_func)(void *data, void *argument)
    , void *argument
);

/*  DLFind
	Search for given data between two given itearatos,
	using the provided compare function

	arguments:
		from - member to start from.
		to - operate until this member (not included).
		cmp_func - the copmarison operation to perform.
		data - the data to search for

	returns iterator to the found data in the list,
	to (argument) if not found.

	complexity O(n)
*/
diter_t DLFind(
 diter_t from,
 diter_t to,
 int(*cmp_func)(const void *data, const void *to_compare),
 const void *to_compare
 );

/*  DLSplice
	Connect two given lists, at given locations (given as iterators)

	arguments:
		dest - connection point
		from - where to start the connection
		to - where to end the connection (not included)

	complexity O(1)
*/
void DLSplice(diter_t from, diter_t to, diter_t dest);



#endif /* DOUBLE_LINK_LIST_H */
