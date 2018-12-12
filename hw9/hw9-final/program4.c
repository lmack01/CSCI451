/*
 * Author - Levi mack
 * Email - levi.mack@UND.edu
 * hw9 - program4.c
 *
 * Compile using:   gcc -pthread program4.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sem.h>
#include <pthread.h>
#include <ctype.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void *monitor1(void *arg);
void *monitor2(void *arg);
void *monitor3(void *arg);
char* var1;
char* var2;
char* var3;

pthread_mutex_t lock;
pthread_cond_t cond;
pthread_cond_t cond2;
pthread_cond_t cond3;

int main (int argc, char** argv) {

	int cr;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	char *fn = "output4.txt";
	cr = creat(fn, mode);

	pthread_mutex_init(&lock, NULL);

	/*  Threading section  */
	pthread_t thread_id, thread_id2, thread_id3;

	pthread_create(&thread_id, NULL, monitor1, NULL); //(void *)array
	usleep(10);
	pthread_create(&thread_id2, NULL, monitor2, NULL);
	usleep(10);
	pthread_create(&thread_id3, NULL, monitor3, NULL);

	pthread_detach(thread_id);
    pthread_detach(thread_id2);
	pthread_detach(thread_id3);

	while(1);
	return 0;
}

void *monitor1(void *arg){
	//monitor program1
	while(1) {
		char *c = (char *) calloc(100, sizeof(char));

		int input = open("output1.txt", O_RDONLY);
		if (input ==-1) {
		    perror("r1");
    	}
		int sz = read(input, c, 10);
		c[sz] = '\0';
		//printf("%s",c);
		close(input);
        if (var1 != c) {
            //printf("var1:%s  c:%s\n",var1,c);
		    pthread_mutex_lock(&lock);
		    int output = open("output4.txt", O_WRONLY | O_APPEND);
		    if (output ==-1) {
		        perror("r1");
        	}
            //if number/character changes write
		    write(output, c, strlen(c)); //-1
		    close(output);

		    pthread_mutex_unlock(&lock);
		    pthread_cond_signal(&cond2);
            var1 = c;
        }
		sleep(0.5);
	}
}

void *monitor2(void *arg){
	//monitor program2
	while(1) {
		char *c = (char *) calloc(100, sizeof(char));

		int input = open("output2.txt", O_RDONLY);
		if (input ==-1) {
		    perror("r2");
    	}
		int sz = read(input, c, 10);
		c[sz] = '\0';
		//printf("%s",c);
		close(input);

        if (var2 != c) {
            //printf("var2:%s  c:%s\n",var2,c);
		    pthread_cond_wait(&cond2, &lock);
		    int output = open("output4.txt", O_WRONLY | O_APPEND);
		    if (output ==-1) {
		        perror("r1");
        	}
            //if character changes write
		    write(output, c, strlen(c)); //-1
		    close(output);

		    pthread_mutex_unlock(&lock);
		    pthread_cond_signal(&cond3);

            var2 = c;
        }
		sleep(0.5);
	}
}

void *monitor3(void *arg){
	//monitor program3
	while(1) {
		char *c = (char *) calloc(100, sizeof(char));

		int input = open("output3.txt", O_RDONLY);
		if (input ==-1) {
		    perror("r3");
    	}
		int sz = read(input, c, 10);
		c[sz] = '\0';
		//printf("%s",c);
		close(input);

        if (var3 != c) {
            //printf("var3:%s  c:%s\n",var3,c);

		    pthread_cond_wait(&cond3, &lock);
		    int output = open("output4.txt", O_WRONLY | O_APPEND);
		    if (output ==-1) {
		        perror("r1");
        	}
            //if character changes write
		    write(output, c, strlen(c)); //-1
		    close(output);

		    pthread_mutex_unlock(&lock);
		    pthread_cond_signal(&cond);

            var3 = c;
        }

		sleep(0.5);
	}
}






