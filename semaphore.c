#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <asm/system.h>
#include <asm/atomic.h>

#include <sys/wait.h>
#include <sys/time.h>

#define atomic_xchg(A,B) __asm__ __volatile__(\
									"lock xchg %1,%0 ;\n"	\
									: "=ir" (A)				\
									: "m" (B), "ir" (A)		\
									);
#define CICLOS 10
#define MAXQUEUE 20

typedef struct _QUEUE {
	pid_t elements[MAXQUEUE];
	pid_t head;
	pid_t tail;
} QUEUE;

typedef struct _semaforo
{
	int count;
	QUEUE *waiting_queue = NULL;
} SEMAFORO;

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

void waitsem(Semaforo sem) 
{
	*sem.count--;
	if(sem.count < 0)
	{
		// agregar proceso a la cola de bloqueados
		// KILL PID SIGSTOP
		
	}
	return;
}

void signalsem(Semaforo *sem) 
{
	sem->count++;
	if(sem->count <= 0)
	{
		pid_t next = _dequeue(sem->waiting_queue);
		kill(next, SIGCONT);
	}
	return;
}

void initsem(Semaforo *sem, int count)
{
	sem = (SEMAFORO *)malloc(sizeof(SEMAFORO));
	sem->count = count;
	sem->waiting_queue = (QUEUE *)malloc(sizeof(QUEUE));
	_initqueue(sem->waiting_queue);
	return;
}