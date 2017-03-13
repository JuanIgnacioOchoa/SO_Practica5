#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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

char *pais[3] = {"Peru", "Bolivia", "Colombia"};

int *g;

struct Semaforo
{
	int count;
};

void waitsem(Semaforo sem) 
{
	*sem.count--;
	if(sem.count < 0)
	{
		// agregar proceso a la cola de bloqueados
		// KILL PID SIGCONT
		
	}
	return;
}

void signalsem(Semaforo sem) 
{
	*sem.count++;
	if(sem.count <= 0)
	{
		//quitar de la cola de bloqueado y agregar a la de listos
		// KILL PID, SIGSTOP
	}
	return
}

Semaforo initsem(Semaforo *sem, int count)
{
	sem.count = count;
}