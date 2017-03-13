#ifndef _semaphore_h
#define _semaphore_h
#include <pthread.h>
#define MAXQUEUE 20

typedef struct _QUEUE {
    pid_t elements[MAXQUEUE];
    pid_t head;
    pid_t tail;
} QUEUE;

typedef struct _semaforo {
    int count;
    QUEUE *waiting_queue;
} SEMAFORO;

void _initqueue(QUEUE *q);

void _enqueue(QUEUE *q, int val);

int _dequeue(QUEUE *q);

void waitsem(SEMAFORO *sem);

void signalsem(SEMAFORO *sem);

void initsem(SEMAFORO *sem, int count);

#endif