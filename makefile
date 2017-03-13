all: semaphores trenes trenes1 trenes2
semaphores:
	gcc -c semaphores.c
trenes:
	gcc -c trenes.c
trenes1:
	gcc -o trenes trenes.o semaphores.o -lpthread
trenes2:
	gcc -o trenes2 trenes2.o semaphores.o -lpthread
