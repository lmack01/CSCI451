/*
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw6-levimack - 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>


int main() {
    key_t key;

    key = ftok("prg0.c", 'a');
    int semid = semget(key, 3, 0666 | IPC_CREAT);
    if (semid < 0) {
        perror("Could Not Create Semaphore");
        exit(1);
    }

    if (semctl(semid, 0, GETVAL, 1)) {
        exit(1);
    }
    if (semctl(semid, 1, GETVAL, 1)) {
        exit(1);
    }
    if (semctl(semid, 2, GETVAL, 1)) {
        exit(1);
    }

    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 0);

	int i;
	for (i=0; i<2; i++) {
		sleep(1);
	}
    printf("Executing process #0.\n");

    return 0;
}

