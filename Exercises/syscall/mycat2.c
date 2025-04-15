#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100

int main()
{
	char buf[COUNT];
	int num_read;
	int fd; 
	
	fd = open("/etc/passwd", O_RDONLY);

	if(fd < 0)
	{
		printf("could not open a file\n");
		exit(-2);
	}

	
	while((num_read = read(fd, buf, COUNT)) > 0)
	{
		if(write(1, buf, num_read) < 0)
		{
			printf("write faild\n");
			exit(-3);
		}	
	}

	return 0;
}
