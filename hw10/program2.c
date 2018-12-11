/*
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw8-levimack: program2.c
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

	//printf("P2 ARGS: %d\n",argc);
	//printf("arg1: %s   arg2: %s   arg3: %s   arg4: %s   arg5: %s   arg5: %s\n",argv[0],argv[1],argv[2],argv[3],argv[4], argv[5]);

	if (argc != 5) {
		printf("Missing Arguments\n");
		exit(1);
	}

	int r1 = atoi(argv[0]);
	//printf("%s\n", r1);
	int w2 = atoi(argv[1]);
	//printf("%s\n", w2);
	int PS1 = atoi(argv[2]);
	//printf("%s\n", PS1);
	int PS2 = atoi(argv[3]);
	//printf("%s\n", PS2);
	int SM = atoi(argv[4]);
	//printf("%s\n", SM);


	int i, vaLM, sz;
	int vowels = 0;
	int consonants = 0;
    char line[250];
    char* str;
    char temp2[250];
    size_t len = 0;
    ssize_t r;


	while ((vaLM = semctl(PS1, 0, GETVAL, NULL)) != 2 ) {
//printf("Sem 1 vaLM: %d\n", vaLM);
		while ((vaLM = semctl(PS1, 0, GETVAL, NULL)) < 1 );
		while ((vaLM = semctl(PS2, 0, GETVAL, NULL)) != 0 );
        memset(temp2, '\0', 250);
        memset(line, '\0', 250);
		if ((sz = read(r1, line, 250)) < 0) {
			printf("Failed to read from read end of pipe.\n");
		}
//printf("sz: %d\n",sz);
//printf("line[0]: %c\n",line[2]);
//    while ((r = getline(&line, &len, fp)) != -1) {
        char temp = tolower(line[0]);
//printf("temp: %c\n",temp);
        if (temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u' || temp == 'y') {
        	vowels++;
        	//if word starts with a vowel do rule 1 of pig latin
		    for (i=0; i<sz; i++) {
		    	if (!isalpha(line[i])) {
		    		if (i==sz) {
						//printf("ray%c\n", line[i]);
						sprintf(temp2,"ray%c", line[i]);
						write(w2, &temp2, strlen(temp2));
						continue;
		    		}
		    		else {
						//printf("ray%c\n", line[i]);
						sprintf(temp2,"ray%c", line[i]);
						write(w2, &temp2, strlen(temp2));
						i++;
						continue;
		    		}
		    	}
		  		if (line[i] == '\n') {
		  			continue;
		  		}
		    	//printf("%c", line[i]);
		    	sprintf(temp2,"%c", line[i]);
	    		write(w2, &temp2, strlen(temp2));
		    }
        }
        else {
        	consonants++;
        	//if word starts with a consonant do rule 2 of pig latin
        	char beg = line[0];
		    for (i=1; i<sz; i++) {
		    	//printf("%c", line[i]);
		    	if (!isalpha(line[i])) {
		    		if (i == sz) {
						//printf("%cay%c", beg, line[i]);
						sprintf(temp2,"%cay%c", beg, line[i]);
		    			write(w2, &temp2, strlen(temp2));
						continue;
					}
		    		else {
						//printf("%cay%c\n", beg, line[i]);
						sprintf(temp2,"%cay%c", beg, line[i]);
			    		write(w2, &temp2, strlen(temp2));
						i++;
						continue;
						}

		    	}
		  		if (line[i] == '\n') {
		  			continue;
		  		}
		    	//printf("%c", line[i]);
		    	sprintf(temp2,"%c", line[i]);
	    		write(w2, &temp2, strlen(temp2));
		    }
        }
		if ((vaLM = semctl(PS1, 0, GETVAL, NULL)) != 2 ) {
			semctl(PS1, 0, SETVAL, 0);
		}
        semctl(PS2, 0, SETVAL, 1);
        //printf("\n");


    }
    //printf("vowels: %d\n", vowels);
    //printf("consonants: %d\n", consonants);
	semctl(PS2, 0, SETVAL, 2);
	while ((vaLM = semctl(PS2, 0, GETVAL, NULL)) < 3);


	int *v = (int *)shmat(SM, 0, 0);
	int *c = v;
	*c++ = vowels;
	*c = consonants;


	semctl(PS2, 0, SETVAL, 4);
	semctl(PS1, 0, IPC_RMID, NULL);
	close(r1);
	exit(0);
	return 0;

}
