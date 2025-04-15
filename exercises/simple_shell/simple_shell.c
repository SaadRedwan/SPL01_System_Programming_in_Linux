#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1000000

int main(int argc, char** argv)
{

    char buf[BUFFER_SIZE];


    while (1) {

	printf("simple shell$ ");
	fgets(buf, BUFFER_SIZE, stdin);

	buf[strlen(buf) - 1] = 0;

	if (strlen(buf) == 0) {
	    continue;
	}

	id_t pid = fork();

	if (pid > 0) {
	    int status;
	    printf("PARENT: my pid = %d. my child pid = %d\n", getpid(),
		   pid);
	    wait(&status);
	    printf("PARENT: my pid = %d. my child pid = %d\n", getpid(),
		   WEXITSTATUS(status));
	} else if (pid == 0) {
	    printf("CHILD: my pid = %d. my parent pid = %d\n", getpid(), getppid());

	    char *newargv[] = { buf, NULL };
	    char *newenvp[] = { NULL };

	    execve(buf, newargv, newenvp);

	    printf("Exec faild: kernel is not the mode of executing programs\n");
	    exit(-1);
	} else {
	    printf("PARENT: faild to fork\n");
	}

    }


    return 0;
}
