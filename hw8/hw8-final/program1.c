/* 
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw8-levimack: program1.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

char curr; //current character being read

int main (int argc, char** argv) {
	
	FILE *fp = fopen("input.data", "r");
	FILE *fp2 = fopen("temp1.data", "w");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"input.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	if (fp2 == NULL) {
		fprintf(stderr, "File (temp1.data) could not be written to.\n");
		exit(1);
	}	
	
	while(fscanf(fp, "%c", &curr) != EOF) {
		if (curr == ' ') {
			fprintf(fp2, "\n");
			//printf("\n");
			continue;
		}	
		fprintf(fp2, "%c", curr);	
		//printf("%c", curr);		
	}
	fclose(fp);
	fclose(fp2);	
	
	exit(0);
	return 0;
	
}
