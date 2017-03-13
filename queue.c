#include <ucontext.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#define MAXQUEUE 20

typedef struct _QUEUE {
	int elements[MAXQUEUE];
	int head;
	int tail;
} QUEUE;

void _initqueue(QUEUE *q)
{
	q->head=0;
	q->tail=0;
}

void _enqueue(QUEUE *q,int val)
{
	q->elements[q->head]=val;
	// Incrementa al apuntador
	q->head++;
	q->head=q->head%MAXQUEUE;
}


int _dequeue(QUEUE *q)
{
	int valret;
	valret=q->elements[q->tail];
	// Incrementa al apuntador
	q->tail++;
	q->tail=q->tail%MAXQUEUE;
	return(valret);
}