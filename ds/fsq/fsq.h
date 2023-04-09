

#ifndef MT_SAFE_FSQ
#define MT_SAFE_FSQ

typedef struct fsq_s fsq_t;

typedef unsigned long size_t;
/*
	creates a new fixed size queue capable to hold
	nmemb integers

	returns:
		handle to new fsq on success, NULL on failure
*/
fsq_t *FSQCreate(size_t nmemb);
/*
	frees all resources associated with fsq
*/
void FSQDestroy(fsq_t *fsq);
/*
	inserts 1 to back of fsq
*/
void FSQEnqueue(fsq_t *fsq, int val);
/*
	removes first in fsq

	returns:
		dequeued element
*/
int FSQDequeue(fsq_t *fsq);

#endif /* MT_SAFE_FSQ */
