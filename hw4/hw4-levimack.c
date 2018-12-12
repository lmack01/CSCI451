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

int value;
pthread_mutex_t lock;
pthread_cond_t cond;
int tf = 0;

void *threadFunct(void *arg);
void *threadFunct2(void *arg);

int main (int argv, char** argc) {

	FILE *fp = fopen("hw4.out", "w");  	//read from downloaded file
	/*  Threading section  */
    	pthread_t thread_id;
    	pthread_t thread_id2;
    	//printf("Before Threads\n");
    	pthread_create(&thread_id, NULL, threadFunct, NULL);
	pthread_create(&thread_id2, NULL, threadFunct2, (void *)fp);
    	pthread_join(thread_id, NULL);
    	pthread_join(thread_id2, NULL);
    	//printf("After Threads\n");
	fclose(fp); //close file after completion
	
	exit(0);
   	return 0;
}

/*  Threading Functions  */

//Read value from hw4.in and then wait for thread 2 to process it
void *threadFunct(void *arg){
    	sleep(1); 
    	//printf("Printing from Thread 1\n");
	FILE *fp = fopen("hw4.in", "r");  	//read from downloaded file
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"hw4.in\" found.\nProgram terminating.\n");
		exit(1);
	}
	while(fscanf(fp, "%d\n", &value) != EOF) {
		//printf("thread 1 read: %d\n", value);
		pthread_mutex_lock(&lock);
		pthread_cond_wait(&cond, &lock);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
	tf = 1;

	fclose(fp);
	return NULL;
}

//Check if value is even or odd then print to hw4.out
void *threadFunct2(void *arg){
    	sleep(5); 
    	//printf("Printing from Thread 2\n"); 
	FILE *inFP = (FILE *) arg;
	while(!tf) {
		//if even print twice
		if ((value % 2) == 0) { 
			fprintf(inFP, "%d\n%d\n", value, value); 
			//printf("%d\n%d\n", value,value);
			//pthread_mutex_lock(&lock);
			pthread_cond_signal(&cond);
			pthread_cond_wait(&cond, &lock);
			pthread_mutex_unlock(&lock);
		}
		//else print once
		else {
			//printf("%d\n", value);
			fprintf(inFP, "%d\n", value); 
			//pthread_mutex_lock(&lock);
			pthread_cond_signal(&cond);
			pthread_cond_wait(&cond, &lock);
			pthread_mutex_unlock(&lock);
		}
	}

	return NULL;
}
