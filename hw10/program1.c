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
#include <sys/sem.h>

char curr; //current character being read

int main (int argc, char** argv) {

	//printf("P1 ARGS: %d\n",argc);
	//printf("arg1: %s   arg2: %s\n",argv[1],argv[2]);

	if (argc != 3) {
		printf("Missing Arguments\n");
		exit(1);
	}

	int w1 = atoi(argv[1]);
	//printf("%s\n", w1);
	int semid = atoi(argv[2]);
	//printf("%s\n", semid);

	FILE *fp = fopen("input.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"input.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	int vaLM, length = 0;
	while(fscanf(fp, "%c", &curr) != EOF) {
		length++;
	}
	//printf("FILE LENGTH: %d\n", length);
	fclose(fp);

	fp = fopen(argv[0], "r");

	char buff[length];
	memset(buff, '\0', length);
	char* word = strtok(fgets(buff, length, fp)," ");
	while (word != NULL) {
		while(( vaLM = semctl(semid, 0, GETVAL, NULL)) > 0){}
		//printf("Program 1: %s\n", word);
		write(w1, word, strlen(word));
		semctl(semid, 0, SETVAL, 1);
		word = strtok(NULL, " ");
		//printf("%d :  %s\n", vaLM, word);
	}
	semctl(semid, 0, SETVAL, 2);
	fclose(fp);
	close(w1);
	exit(0);
	return 0;

}
