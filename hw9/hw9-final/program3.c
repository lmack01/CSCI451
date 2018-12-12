/************************************************/
/* Produces a character once every 120 seconds. */
/************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
int main(void) {
    /*int key = ftok("program3.c", 'a');
    int semid = semget(key, 1, 0660 | IPC_CREAT);
    if (semid < 0) {
        perror("Could Not Create Semaphore");
        exit(1);
    }*/
    
	int i;
	char number;
	FILE *output;
    while (1) {
       for (i = 58; i < 127; i++) {
	   		//semctl(semid, 0, SETVAL, 1);	
			output = fopen("./output3.txt", "w");
			fprintf(output, "%c\n", i);
			fclose(output);
	   		//semctl(semid, 0, SETVAL, 0);	
			sleep(120);
       }
    }
    return 1;
}

