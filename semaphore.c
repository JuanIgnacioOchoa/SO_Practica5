#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <asm/system.h>
#include <asm/atomic.h>
#include "semaphore.h"

#include <sys/wait.h>
#include <sys/time.h>

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

void waitsem(SEMAFORO *sem) 
{
	sem->count--;
	if(sem.count < 0)
	{
		// agregar proceso a la cola de bloqueados
		// KILL PID SIGSTOP
		_enqueue(sem->waiting_queue, getpid())
		kill(getpid(), SIGSTOP);

	}
	return;
}

void signalsem(SEMAFORO *sem) 
{
	sem->count++;

	if(sem->count <= 0)
	{
		pid_t next = _dequeue(sem->waiting_queue);
		kill(next, SIGCONT);
	}
	return;
}

void initsem(SEMAFORO *sem, int count)
{
	*sem.count = count;

	sem = (SEMAFORO *)malloc(sizeof(SEMAFORO));
	sem->count = count;
	sem->waiting_queue = (QUEUE *)malloc(sizeof(QUEUE));
	_initqueue(sem->waiting_queue);
	return;

}