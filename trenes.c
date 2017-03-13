#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "semaphore.h"

#define CICLOS 10

char *pais[3] = {"Peru", "Bolivia", "Colombia"};

SEMAFORO *sem;

void *proceso(void *arg) {

	int i = *((int *)arg);
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
	//Implementación de Semáforos.
	//Sistemas Operativos, Primavera 2017
	// Crea los hilos
	for(i=0;i<3;i++)
	{
		args[i]=i;
		res = pthread_create(&tid[i], NULL, proceso, (void *) &args[i]);
	}
	// Espera que terminen los hilos
	for(i=0;i<3;i++)
		res = pthread_join(tid[i], &thread_result);
	return 0;
}