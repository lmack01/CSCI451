/*
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw6-levimack - 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    int key = ftok("prg0.c", 'a');
    int semid = semget(key, 3, 0666 | IPC_CREAT);
    if (semid < 0) {
        perror("Could Not Create Semaphore");
        exit(1);
    }
    if (semctl(semid, 1, GETVAL, NULL) != 1) {
        exit(1);
    }

	int i;
	for (i=0; i<2; i++) {
		sleep(1);
	}
    printf("Executing process #2.\n");
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 1);

    return 0;
}
