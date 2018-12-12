/*
 * Author - Levi Mack
 * Email - levi.mack@UND.edu
 * hw3-levimack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

void *threadFunct(void *arg);
void *threadFunct2(void *arg);

int main (int argv, char** argc) {

	system("wget http://undcemcs01.und.edu/~ronald.marsh/CLASS/CS451/hw3-data.txt");	//download file from website
	FILE *fp = fopen("hw3-data.txt", "r");  	//read from downloaded file

	int ch;
	int x = 0;
	int size = 1;  					        //initial size of the dynamic array
	char *carr = malloc(size);  			//allocate initial memory for character array
	while ((ch = getc(fp)) != EOF) {    	//scan file char-by-char

		if(carr == NULL){			        //if pointer null, out of memory
    			fprintf(stderr, "out of memory\n");
    			exit(1);
    		}				
		if (size >= x-1) {
       			size += 1;		
        		carr = realloc(carr, size);	//allocate more memory as needed
       			if(carr == NULL) {
           			fprintf(stderr, "out of memory\n");
           			exit(1);
            		}
		}
		if (isupper(ch)) {
			//putc(tolower(ch), stdout);
			ch = tolower(ch);		        //convert characters to lowercase
			carr[x] = ch;			        //add character to array
		
		} else {
			//putc(ch, stdout);
			carr[x] = ch;			        //add character to array (already lowercase)
		}
		x++;
	}
	carr[x++] = '\0';				        //add terminating character


	/*  TESTING SECTION  */

	/*printf("%d\n",x);	
	int i;
	for(i=0; i < size; i++) {
		//printf("%c", carr[i]);		        //print message char-by-char
		//printf("%d\n", carr[i]);		        //print character numeric vals
	}*/
	

	/*  Threading section  */
    	pthread_t thread_id;
    	pthread_t thread_id2;
    	//printf("Before Threads\n");
    	pthread_create(&thread_id, NULL, threadFunct, (void *)carr);
	    pthread_create(&thread_id2, NULL, threadFunct2, (void *)carr);
    	pthread_join(thread_id, NULL);
    	pthread_join(thread_id2, NULL);
    	//printf("After Threads\n");

	int i;
	for(i=0; i < x; i++) { 
		carr[i] = 0;
	}
	size = 0;
	free(carr);   	


	exit(0);
   	return 0;
}

/*  Threading Search Functions  */

//Search char array for "easy"
void *threadFunct(void *arg){
    	sleep(1); 
    	//printf("Printing from Thread 1\n");
	    int occ = 0;		//number of occurances
	    char *inCarr = (char *) arg; 
	    while((inCarr = strstr(inCarr, "easy")) != NULL) {
	    	inCarr += 4;
	    	occ++;
	    } 
	    printf("\"easy\" occurances: %d\n", occ);
	    return NULL;
}

//Search char array for "polar"
void *threadFunct2(void *arg){
    	sleep(1); 
    	//printf("Printing from Thread 2\n"); 
	
	    int occ = 0;		//number of occurances
	    char *inCarr = (char *) arg;
	    while((inCarr = strstr(inCarr, "polar")) != NULL) {
	    	inCarr += 4;
	    	occ++;
	    } 
	    printf("\"polar\" occurances: %d\n", occ);
	    return NULL;
}
