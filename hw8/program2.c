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


int main (int argc, char** argv) {
	
	FILE *fp = fopen("temp1.data", "r");
	FILE *fp2 = fopen("temp2.data", "w"); //pig latin
	FILE *fp3 = fopen("shared1.dat", "w");	//words starting with vowel
	FILE *fp4 = fopen("shared2.dat", "w");	//words starting with consonant
	
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"temp1.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	if (fp2 == NULL) {
		fprintf(stderr, "File (temp2.data) could not be written to.\n");
		exit(1);
	}	
	if (fp3 == NULL) {
		fprintf(stderr, "File (shared1.dat) could not be written to.\n");
		exit(1);
	}	
	if (fp4 == NULL) {
		fprintf(stderr, "File (shared2.dat) could not be written to.\n");
		exit(1);
	}	

	int i;
	int vowels = 0;
	int consonants = 0;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    
    while ((read = getline(&line, &len, fp)) != -1) {
        char temp = tolower(line[0]);
        char* new;
        if (temp == 'a' || temp == 'e' || temp == 'i' || temp == 'o' || temp == 'u' || temp == 'y') { 
        	vowels++;
        	//if word starts with a vowel do rule 1 of pig latin
		    for (i=0; i<read; i++) {
		    	if (!isalpha(line[i])) {
		    		//printf("ray%c", line[i]);
		    		fprintf(fp2, "ray%c", line[i]);
		    		fprintf(fp3, "ray%c", line[i]);
		    	}
		  		if (line[i] == '\n') {
		  			continue;
		  		}
		    	//printf("%c", line[i]);		
		    	fprintf(fp2, "%c", line[i]);
		    	fprintf(fp3, "%c", line[i]);
		    }        	
        }
        else {
        	consonants++;
        	//if word starts with a consonant do rule 2 of pig latin
        	char beg = line[0];
		    for (i=1; i<read; i++) {
		    	//printf("%c", line[i]);
		    	if (!isalpha(line[i])) {
		    		if (i == read-1) {
						//printf("%cay%c", beg, line[i]);
						fprintf(fp2, "%cay%c", beg, line[i]);
						fprintf(fp4, "%cay%c", beg, line[i]);
						continue;
					}
		    		else {
						//printf("%cay%c\n", beg, line[i]);
						fprintf(fp2, "%cay%c\n", beg, line[i]);
						fprintf(fp4, "%cay%c\n", beg, line[i]);		    		
						i++;
						continue;
						}
		    			    	
		    	}	
		  		if (line[i] == '\n') {
		  			continue;
		  		}
		    	//printf("%c", line[i]);		
		    	fprintf(fp2, "%c", line[i]);
		    	fprintf(fp4, "%c", line[i]);		  				    		    	
		    }  
        }        
    }	
    //printf("\nshared1.dat: %d\n", vowels);
    //printf("shared2.dat: %d\n", consonants);	
				
	fclose(fp);
	fclose(fp2);	
	fclose(fp3);
	fclose(fp4);
		
	exit(0);
	return 0;	
	
}
