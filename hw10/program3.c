/*
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw8-levimack: program3.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/shm.h>

int main (int argc, char** argv) {

	//printf("P3 ARGS: %d\n",argc);
	//printf("arg1: %s   arg2: %s   arg3: %s   arg4: %s   arg5: %s\n",argv[0],argv[1],argv[2],argv[3],argv[4]);

	if (argc != 4) {
		printf("Missing Arguments\n");
		exit(1);
	}

	char* outfile = argv[0];
	//printf("%s\n", r1);
	int r2 = atoi(argv[1]);
	//printf("%s\n", w2);
	int PS2 = atoi(argv[2]);
	//printf("%s\n", PS1);
	int SM = atoi(argv[3]);
	//printf("%s\n", PS2);


	FILE *fp = fopen(outfile, "w");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"output.data\" found.\nProgram terminating.\n");
		exit(1);
	}

	int sz, vaLM, i;
	char ch;
	char line[250];

	while ((vaLM = semctl(PS2, 0, GETVAL, NULL)) < 2 ) {
		while ((vaLM = semctl(PS2, 0, GETVAL, NULL)) < 1 );
		if ((sz = read(r2, line, 250)) < 0) {
			//printf("Failed to read from read end of pipe.\n");
			break;
		}
		//printf("P3: sz: %d\n",sz);
		//printf("Program 3: %s\n", line);
		for (i = 0; i<sz; i++) {
			fprintf(fp, "%c", line[i]);
		}
		fprintf(fp, " ");
		memset(line, '\0', 250);

		if ((vaLM = semctl(PS2, 0, GETVAL, NULL)) < 2 ) {
			semctl(PS2, 0, SETVAL, 0);
		}
	}
	semctl(PS2, 0, SETVAL, 3);
	while ((vaLM = semctl(PS2, 0, GETVAL, NULL)) < 4 );
	semctl(PS2,0 ,IPC_RMID, 0);

	int *vowels = (int *)shmat(SM, 0, 0);
	int *consonants = vowels;
	*consonants++;
	printf("Type_1: %d\n", *vowels);
	printf("Type_2: %d\n", *consonants);
	shmdt(vowels);
	shmctl(SM, IPC_RMID, NULL);
	semctl(PS2, 0, IPC_RMID, NULL);
	close(r2);
	fclose(fp);

	exit(0);
	return 0;
}
