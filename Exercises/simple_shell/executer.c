#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

	if(argc < 2) {
		printf("Usage: %s path of elf\n", argv[0]);
		exit(-1);
	}


	getchar();

	char *newargv[] = {argv[0], NULL};
	char *newenvp[] = {NULL};
	
	execve(argv[1], newargv, newenvp);

	printf("Exec faild: kernel is not the mode of executing programs\n");
	return -2;
}
	
