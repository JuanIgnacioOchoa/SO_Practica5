#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "semaphore.h"

#include <sys/wait.h>
#include <sys/time.h>


void _initqueue(QUEUE *q)
{
	q->head=0;
	q->tail=0;
}

void _enqueue(QUEUE *q,pid_t val)
{
	q->elements[q->head]=val;
	// Incrementa al apuntador
	q->head++;
	q->head=q->head%MAXQUEUE;
}

pid_t _dequeue(QUEUE *q)
{
	int valret;
	valret=q->elements[q->tail];
	// Incrementa al apuntador
	q->tail++;
	q->tail=q->tail%MAXQUEUE;
	return(valret);
}

void waitsem(SEMAFORO *sem) 
{
	//printf("hola 6\n");
	pthread_mutex_lock(&(sem->count_mutex));
	sem->count--;
	pthread_mutex_unlock(&(sem->count_mutex));
	if(sem->count < 0)
	{
		printf("hola 7\n");
		// agregar proceso a la cola de bloqueados
		// KILL PID SIGSTOP
		_enqueue(sem->waiting_queue, getpid());

		printf("hola pid      %d\n",getpid());
		printf("hola _dequeue %d\n", _dequeue(sem->waiting_queue));
		_enqueue(sem->waiting_queue,getpid());
		
		//kill(getpid(), SIGSTOP);

	}
	return;
}

void signalsem(SEMAFORO *sem) 
{
	pthread_mutex_lock(&(sem->count_mutex));
	sem->count++;
	pthread_mutex_unlock(&(sem->count_mutex));

	if(sem->count <= 0)
	{
		pid_t next = _dequeue(sem->waiting_queue);
		kill(next, SIGCONT);
	}
	return;
}

SEMAFORO* initsem(int count)
{	
	SEMAFORO *sem;
	sem = (SEMAFORO *)malloc(sizeof(SEMAFORO));
	sem->count = count;
	sem->waiting_queue = (QUEUE *)malloc(sizeof(QUEUE));
	_initqueue(sem->waiting_queue);
	return sem;
}