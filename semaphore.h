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
    pthread_mutex_t count_mutex;
} SEMAFORO;

void _initqueue(QUEUE *q);

void _enqueue(QUEUE *q, pid_t val);

pid_t _dequeue(QUEUE *q);

void waitsem(SEMAFORO *sem);

void signalsem(SEMAFORO *sem);

SEMAFORO* initsem(int count);

#endif