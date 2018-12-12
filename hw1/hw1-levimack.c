/*
 * Author - Levi Mack
 * Email - levi.mack@UND.edu
 * hw1.levimack.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argv, char** argc) {
    if (argv < 2 || argv > 5) {
        printf("You've provided either too many or too few arguments.\n");
    }
    else {
	char syscmd[30];
	//for each argument, execute system command of that arg
	for (int i = 1; i < argv; i++) {
		strcpy(syscmd, argc[i]);
		strcat(syscmd," >> output.txt");
		//printf("arg: %s\n", argc[i]);
		system(syscmd);
	}
    }
    return 0;
}
