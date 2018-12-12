/*
 * Author - Levi mack
 * Email - levi.mack@und.edu
 * hw3-levimack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argv, char** argc) {
	int exitC = 1;
	pid_t PID = fork();
	
	if (PID == 0){
		//printf("CHILD: Hello from child.\n");
		execl("/usr/bin/X11/xclock","/usr/bin/X11/xclock", NULL);
	} else {
		execl("./a.out","./a.out", NULL);
		//printf("PARENT: Spawning child PID: %d\n", PID);
		waitpid(PID, &exitC, 0);
		//printf("PARENT: Child exit code: %d\n",(exitC >> 8));
	}
	return 0;
}
