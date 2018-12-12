/************************************************/
/* Produces an odd value once every 30 seconds. */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
int main(void) {
   /* int key = ftok("program2.c", 'a');
    int semid = semget(key, 1, 0660 | IPC_CREAT);
    if (semid < 0) {
        perror("Could Not Create Semaphore");
        exit(1);
    }*/
        
	int i;
	char number;
	FILE *output;
    while (1) {
       for (i = 1; i < 10; i+=2) {
	   //		semctl(semid, 0, SETVAL, 1);	
           output = fopen("./output2.txt", "w");
           fprintf(output, "%d\n", i);
           fclose(output);
	   //		semctl(semid, 0, SETVAL, 0);	
           sleep(30);
       }
    }
    return 1;
}


