/* 
 * Author - Levi Mack
 * email - levi.mack@UND.edu
 * hw5-levimack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>
#include <unistd.h>

struct page {
	int PID;
	int R;
	int M;
	int locked;
};

void *threadFunct(void *arg);
void *threadFunct2(void *arg);
void *threadFunct3(void *arg);
void *threadFunct4(void *arg);

int tf;
pthread_mutex_t lock;
pthread_cond_t cond;

int main (int argc, char** argv) {

	struct page* array = malloc(5000 * sizeof(struct page));
	srand(1492);
	int i;
	for (i = 0; i < 5000; i++) {
		array[i].R = 0;
		array[i].M = 0;
		array[i].locked = 0;

	}
	/*  Threading section  */
	pthread_t thread_id;
	pthread_t thread_id2;
	pthread_t thread_id3;
	pthread_t thread_id4;

	pthread_create(&thread_id, NULL, threadFunct, (void *)array);
//printf("start\n");
	pthread_create(&thread_id2, NULL, threadFunct2, (void *)array);
//printf("start\n");
	pthread_create(&thread_id3, NULL, threadFunct3, (void *)array);
//printf("start\n");
	pthread_create(&thread_id4, NULL, threadFunct4, (void *)array);
//printf("start\n");

	pthread_join(thread_id, NULL);
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
	pthread_join(thread_id4, NULL);    	
//printf("end\n");

	free(array);
	exit(0);
	return 0;
}

void *threadFunct(void *arg){
	struct page *array = (struct page *)arg;
	while (!tf) {
		pthread_mutex_lock(&lock);
		int p2m = rand() % (4999 + 1 - 0) + 0;
		int bit = rand() % 2;
		array[p2m].PID = 100;	
		if (array[p2m].locked == 0) {		
			array[p2m].locked = 1;
			if (bit == 0) {
				array[p2m].R = 1;
				array[p2m].M = 0;
			} else if (bit == 1) {
				array[p2m].R = 1;
				array[p2m].M = 1;
			}
			//array[p2m].locked = 0;
		} else {
			printf("Thread 1: Page Fault: %d\n", p2m);
		}
		pthread_mutex_unlock(&lock);		
	}
}

void *threadFunct2(void *arg){
	struct page *array = (struct page *)arg;
	while (!tf) {
		pthread_mutex_lock(&lock);
		int p2m = rand() % (4999 + 1 - 0) + 0;
		int bit = rand() % 2;
		array[p2m].PID = 200;	
		if (!array[p2m].locked) {		
			array[p2m].locked = 1;
			if (bit == 0) {
				array[p2m].R = 1;
				array[p2m].M = 0;
			} else if (bit == 1) {
				array[p2m].R = 1;
				array[p2m].M = 1;
			}
			//array[p2m].locked = 0;
		} else {
			printf("Thread 2: Page Fault: %d\n", p2m);
		}
		pthread_mutex_unlock(&lock);		
	}
}

void *threadFunct3(void *arg){
	struct page *array = (struct page *)arg;
	while (!tf) {
		pthread_mutex_lock(&lock);
		int p2m = rand() % (4999 + 1 - 0) + 0;
		int bit = rand() % 2;
		array[p2m].PID = 300;	
		if (!array[p2m].locked) {		
			array[p2m].locked = 1;
			if (bit == 0) {
				array[p2m].R = 1;
				array[p2m].M = 0;
			} else if (bit == 1) {
				array[p2m].R = 1;
				array[p2m].M = 1;
			}
			//array[p2m].locked = 0;
		} else {
			printf("Thread 3: Page Fault: %d\n", p2m);
		}
		pthread_mutex_unlock(&lock);		
	}
}

void *threadFunct4(void *arg){
	struct page *array = (struct page *)arg;	
	while (!tf) {
		int x;		
		for (x=0; x<5000; x++) {
			pthread_mutex_lock(&lock);
			if (array[x].M == 0 && array[x].locked == 1) {
				array[x].R = 0;
				array[x].M = 0;
				array[x].locked = 0;
			} else if (array[x].M == 1) {
				array[x].R = 0;
				array[x].M = 0;
				array[x].locked = 0;
				sleep(0.5);
			}
			pthread_mutex_unlock(&lock);		
		}
	}
}
