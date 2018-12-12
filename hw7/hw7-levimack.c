/* 
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw7-levimack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

void *threadFunct(void *arg);
void *threadFunct2(void *arg);
void *threadFunct3(void *arg);
void *threadFunct4(void *arg);
void *threadFunct5(void *arg);

int r1 = 1;//running bool
int r2 = 1;//running bool
int r3 = 1;//running bool
int r4 = 1;//running bool
int r5 = 1;//running bool

char curr; //current character being read by a thread
char *output;
size_t n = 0;

pthread_mutex_t lock;

pthread_cond_t cond;
pthread_cond_t cond2;
pthread_cond_t cond3;
pthread_cond_t cond4;
pthread_cond_t cond5;

int main (int argc, char** argv) {
	
	FILE *fp = fopen("drive1.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive1.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	//get file size and create data structure
	fseek(fp, 0L, SEEK_END);
	int sz = ftell(fp) * 5;
	//printf("file size: %d\n", sz);
	fclose(fp);


    output = malloc(sz);
	int i;    
	for (i=0; i < sz; i++)
    {
        output[i] = ' ';
    }

	/*  Threading section  */
	pthread_t thread_id;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;
	pthread_t thread_id5;

	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread_id, NULL, threadFunct, NULL); 
	pthread_detach(thread_id);
	//usleep(500);
	pthread_create(&thread_id2, NULL, threadFunct2, NULL);
	pthread_detach(thread_id2);
	//usleep(500);
	pthread_create(&thread_id3, NULL, threadFunct3, NULL);
	pthread_detach(thread_id3);
	//usleep(500);
	pthread_create(&thread_id4, NULL, threadFunct4, NULL);
	pthread_detach(thread_id4);
	//usleep(500);
	pthread_create(&thread_id5, NULL, threadFunct5, NULL);
	pthread_detach(thread_id5);
	//usleep(500);

	while(1) {	
		if (r1==0 | r2==0 | r3==0 | r4==0 | r5==0) {
			break;
		}
	}

    for (i=0; i < sz * 5; i++)
    {
        printf("%c", output[i]);
    }
    printf("\n");

	exit(0);
	return 0;
}

void *threadFunct(void *arg){
	usleep(500);
	//printf("HEllo from thread 1\n");
	FILE *fp = fopen("drive1.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive1.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	while(fscanf(fp, "%c", &curr) != EOF) {
		//printf("%c", curr);
		output[n++] = curr;
		//read char and then wait for thread 2
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond2);
		pthread_cond_wait(&cond, &lock);		
	}
	fclose(fp);
	r1 = 0; //running bool
}

void *threadFunct2(void *arg){
	//printf("HEllo from thread 2\n");
	FILE *fp = fopen("drive2.data", "r");	
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive2.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	while(fscanf(fp, "%c", &curr) != EOF) {
		pthread_cond_wait(&cond2, &lock);		
		//printf("%c", curr);
		output[n++] = curr;
		//read char and then wait for thread 3
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond3);
	}
	fclose(fp);
	r2 = 0;//running bool
}

void *threadFunct3(void *arg){
	//printf("HEllo from thread 3\n");
	FILE *fp = fopen("drive3.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive3.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	while(fscanf(fp, "%c", &curr) != EOF) {
		pthread_cond_wait(&cond3, &lock);		
		//printf("%c", curr);
		output[n++] = curr;
		//read char and then wait for thread 4
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond4);
	}
	fclose(fp);
	r3 = 0;//running bool
}

void *threadFunct4(void *arg){
	//printf("HEllo from thread 4\n");
	FILE *fp = fopen("drive4.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive4.data\" found.\nProgram terminating.\n");
		exit(1);
	}
	while(fscanf(fp, "%c", &curr) != EOF) {
		pthread_cond_wait(&cond4, &lock);		
		//printf("%c", curr);
		output[n++] = curr;
		//read char and then wait for thread 5
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond5);
	}
	fclose(fp);
	r4 = 0;//running bool
}

void *threadFunct5(void *arg){
	//printf("HEllo from thread 5\n");
	FILE *fp = fopen("drive5.data", "r");
	if (fp == NULL) {
		fprintf(stderr, "File Not Found: \nNo input file called \"drive5.data\" found.\nProgram terminating.\n");
		exit(1);
	}	
	while(fscanf(fp, "%c", &curr) != EOF) {
		pthread_cond_wait(&cond5, &lock);		
		//printf("%c", curr);
		output[n++] = curr;
		//read char and then wait for thread 1
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&cond);
	}
	fclose(fp);
	r5 = 0;//running bool
}