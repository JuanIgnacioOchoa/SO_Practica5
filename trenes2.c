#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <asm/system.h>
#include <asm/atomic.h>

#include <sys/wait.h>
#include <sys/time.h>

#define CICLOS 10

char *pais[3] = {"Peru", "Bolivia", "Colombia"};



void proceso(int i, int segment_id) {
	SEMAFORO *sem = shmat(segment_id,NULL,0);
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
	SEMAFORO *sem;
	initsem(sem, 1);
	int segment_id = shmget(IPC_PRIVATE, sizeof(sem), S_IRUSR | S_IWUSR);
	pid_t tid[3];

	int res;
	int args[3];
	int i;
	void *thread_result;
	srand(getpid());
	sem = shmat(segment_id, NULL, 0);
	//Implementación de Semáforos.
	//Sistemas Operativos, Primavera 2017
	// Crea los procesos
	for(i=0;i<3;i++)
	{
		pid_t t;
		t = fork();
		if(t > 0) {
			proceso(i, segment_id);
		}
	}
	// Espera que terminen los hilos
	for(i=0;i<3;i++)
		res = pthread_join(tid[i], &thread_result);
	return 0;
}