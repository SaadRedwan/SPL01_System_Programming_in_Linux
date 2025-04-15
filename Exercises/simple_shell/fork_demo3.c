#include <stdio.h>
#include <unistd.h>

int x = 5;
int y;

int main() {

	int z =10;
	getchar();

	x++; y++; z++;
	printf("PARENT: before fork x = %d, y = %d, z = %d\n", x, y, z);
	pid_t pid = fork();

	if(pid > 0) {
		while(1) {
			printf("PARENT: my pid = %d. my child pid = %d\n", getpid(), pid);
			printf("PARENT: after fork x = %d, y = %d, z = %d\n", x, y, z);
			x++; y++; z++;
			usleep(500000);
		}
	} else if(pid == 0) { 
		
		while(1) {
			printf("CHILD: my pid = %d. my parent pid = %d\n", getpid(), getppid());
			usleep(500000);
			printf("CHILD: after fork x = %d, y = %d, z = %d\n", x, y, z);
			x++; y++; z++;
			x++; y++; z++;
			x++; y++; z++;
		}
	} else {
		printf("PARENT: faild to fork\n");
	}

	getchar();

	return 0;
}
