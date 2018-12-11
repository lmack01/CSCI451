/*
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw8-levimack: program1.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int main (int argc, char** argv) {

//printf("arg1 %s      arg2 %s\n",argv[1],argv[2]);
	if (argc < 3) {
		printf("USAGE: ./filename input.data temp3.data\n");
		exit(1);
	}

	char* inputFile = argv[1];
	char* outputFile = argv[2];

	//create pipes
	int pfd1[2]; //pipe 1
	int pfd2[2]; //pipe 2
	if (pipe(pfd1) == -1) {
		printf("Pipe 1 Failed.");
		exit(1);
	}

	if (pipe(pfd2) == -1) {
		printf("Pipe 2 Failed.");
		exit(1);
	}
	//make them strings to send via execv
	char r1[250], w1[250], r2[250], w2[250];
	sprintf(w1, "%d", pfd1[1]);		//write side pipe 1
	//printf("%s\n", w1);
	sprintf(r1, "%d", pfd1[0]);		//read side pipe 1
	//printf("%s\n", r1);
	sprintf(w2, "%d", pfd2[1]);		//write side pipe 2
	//printf("%s\n", w2);
	sprintf(r2, "%d", pfd2[0]);		//read side pipe 2
	//printf("%s\n", r2);

	//create semaphores
	key_t s1 = ftok(inputFile ,'a');
	key_t s2 = ftok(outputFile,'a');
	int semid1 = semget(s1, 1, 0660 | IPC_CREAT);
	if (semid1 < 0) {
		printf("Could not create Semaphore 1.\n");
		exit(1);
	}
	int semid2 = semget(s2, 1, 0660 | IPC_CREAT);
	if (semid2 < 0) {
		printf("Could not create Semaphore 2.\n");
		exit(1);
	}
	semctl(semid1, 0, SETVAL, 0);
	semctl(semid2, 0, SETVAL, 0);
	//make them strings to send via execv
	char PS1[250], PS2[250];
	sprintf(PS1, "%d", semid1);		//semaphore 1
	//printf("%s\n", PS1);
	sprintf(PS2, "%d", semid2);		//semaphore 2
	//printf("%s\n", PS2);


	//create shared memory
	key_t memkey = ftok("master.c",'a');
	int memid = shmget(memkey, 27, 0600 | IPC_CREAT);
	if (memid < 0) {
		printf("Could not create shared memory segment.");
		exit(1);
	}
	//convert to string to send via execv
	char SM[250];
	sprintf(SM, "%d", memid);
	//printf("%s\n", SM);


	int PID1 = fork();
	if (PID1 == 0) {	//executed by the child process
		//printf("child1 %d\n",PID1);

		char* args[] = {inputFile, w1, PS1, NULL};
		//system("gcc program1.c -o p1.out");
		if (execv("p1.out", args) == -1) {
			printf("execution of p1.out failed\n");
		}
		exit(0);
	}
	//printf("parent1 %d\n",PID1);

	int PID2 = fork();
	if (PID2 == 0) {	//executed by the child process
		//printf("child2 %d\n",PID2);

		char* args[] = {r1, w2, PS1, PS2, SM, NULL};
		//system("gcc program2.c -o p2.out");
		if (execv("p2.out", args) == -1) {
			printf("execution of p2.out failed\n");
		}
		exit(0);
	}
	//printf("parent2 %d\n",PID2);

	int PID3 = fork();
	if (PID3 == 0) {	//executed by the child process
		//printf("child3 %d\n",PID3);

		char* args[] = {outputFile, r2, PS2, SM, NULL};
		//system("gcc program3.c -o p3.out");
		if (execv("p3.out", args) == -1) {
			printf("execution of p3.out failed\n");
		}
		exit(0);
	}
	//printf("parent3 %d\n",PID3);*/

	int stat;
	waitpid(PID1, &stat, 0);
	waitpid(PID2, &stat, 0);
	waitpid(PID3, &stat, 0);
	exit(0);
	return 0;

}
