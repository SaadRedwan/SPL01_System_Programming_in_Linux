#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define COUNT 100


int mycat_main(int argc, char** argv);



int main(int argc, char** argv)
{
	mycat_main(argc, argv);
	return 0;
}


int mycat_main(int argc, char** argv){

	        if(argc != 2)
        {
                fprintf(stderr, "Usage: %s file-name\n", argv[0]);
                exit(-1);
        }
        char buf[COUNT];
        int num_read;
        int fd;

        fd = open(argv[1], O_RDONLY);

        if(fd < 0)
        {
                fprintf(stderr, "could not open a file\n");
                exit(-2);
        }


        while((num_read = read(fd, buf, COUNT)) > 0)
        {
                if(write(1, buf, num_read) < 0)
                {
                        fprintf(stderr, "write faild\n");
                        exit(-3);
                }
        }
        close(fd);

	return 0;
}
	
