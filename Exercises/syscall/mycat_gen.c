#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100


int mycat_gen_main(int argc, char** argv);

int main(int argc, char** argv)
{

	mycat_gen_main(argc, argv);

	return 0;
}




int mycat_gen_main(int argc, char** argv) {
	
	if(argc != 1)
	{
		char buf[COUNT];
		int fd, num_read; 
		int i;


		for(i=1; i < argc; i++)
		{
			printf("Content of %s: \n\n", argv[i]);
			
			fd = open(argv[i], O_RDONLY);

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
			close(fd);
			printf("\n\n\n");
		}
	}
	else
	{	
		printf("Usage: %s file-name\n", argv[0]);
		exit(-1);
	}
	
	return 0;
}
