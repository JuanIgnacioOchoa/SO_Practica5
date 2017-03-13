all: semaphores trenes mirapendejo trenes1 trenes2
semaphores:
	gcc -c semaphore.c
trenes:
	gcc -c trenes.c
mirapendejo:
	gcc -c trenes2.c
trenes1:
	gcc -o trenes trenes.o semaphore.o -lpthread
trenes2:
	gcc -o trenes2 trenes2.o semaphore.o -lpthread
