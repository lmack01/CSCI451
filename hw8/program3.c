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


int main (int argc, char** argv) {

	FILE *fp = fopen("shared1.dat", "r");
	FILE *fp2 = fopen("shared2.dat", "r");	
	FILE *fp3 = fopen("temp2.data", "r");		
	
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"shared1.dat\" found.\nProgram terminating.\n");
		exit(1);
	}
	if (fp2 == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"shared2.dat\" found.\nProgram terminating.\n");
		exit(1);
	}
	if (fp3 == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"temp2.data\" found.\nProgram terminating.\n");
		exit(1);
	}		
	
	int vowels = 0;
	int consonants = 0;
	char ch;
	
	while (!feof(fp)) {
		ch = fgetc(fp);
		if (ch == '\n') {
			vowels++;
		}
	}

	while (!feof(fp2)) {
		ch = fgetc(fp2);
		if (ch == '\n') {
			consonants++;
		}
	}	
	
	printf("Type_1: %d\n", vowels);
	printf("Type_2: %d\n", consonants);

	system("tr '\n' ' ' < temp2.data > temp3.data");
	
	fclose(fp);
	fclose(fp2);	
	fclose(fp3);
	
	exit(0);
	return 0;		
}
