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
	atomic_t count;
	int sleepers;
	wait_queue_head_t wait;
};

void waitsem(Semaforo sem) {
	sem.count--;
	return;
}

void signalsem(Semaforo sem) {
	sem.count++;
	return
}

Semaforo initsem(in)

void proceso(int i) {
	int k;
	for(k=0;k<CICLOS;k++)
	{
		// Llamada waitsem implementada en la parte 3
		waitsem(sem);
		printf("Entra %s ",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		// Llamada waitsignal implementada en la parte 3
		signalsem(sem);
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0);
	// Termina el proceso
}

int main(int argc, char const *argv[])
{
	initsem(sem, 1);
	pthread_t tid[3];
	int res;
	int args[3];
	int i;
	void *thread_result;
	srand(getpid());
	3Implementación de Semáforos.
	Sistemas Operativos, Primavera 2017
	// Crea los hilos
	for(i=0;i<3;i++)
	{
	args[i]=i;
	res = pthread_create(&tid[i], NULL, hilo1, (void *) &args[i]);
	}
	// Espera que terminen los hilos
	for(i=0;i<3;i++)
	res = pthread_join(tid[i], &thread_result);
	return 0;
}