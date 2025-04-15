#include <stdio.h>
#include <unistd.h>


int main() {

	getchar();

	pid_t pid = fork();

	if(pid > 0) {
		while(1) {
			printf("PARENT: my pid = %d. my child pid = %d\n", getpid(), pid);
			usleep(500000);
		}
	} else if(pid == 0) { 
		
		while(1) {
			printf("CHILD: my pid = %d. my parent pid = %d\n", getpid(), getppid());
			usleep(500000);
		}
	} else {
		printf("PARENT: faild to fork\n");
	}

	getchar();

	return 0;
}
