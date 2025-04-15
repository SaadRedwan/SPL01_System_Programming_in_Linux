#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#define BUF_SIZE 8192   //8K chunk

mycp_main(int argc, char** argv);


int main(int argc, char** argv)
{
	mycp_main(argc, argv);

	return 0;
}


int mycp_main(int argc, char** argv){
if(argc != 3)
	{
		fprintf(stderr, "Usage %s source destination\n", argv[0]);
		exit(-1);
	}

	const char* src = argv[1];
	const char* dst = argv[2];
	int fd_src, fd_dst;
	char read_buf[BUF_SIZE];
	int read_count;


	fd_src = open(src, O_RDONLY);

	if(fd_src == -1)
	{
		fprintf(stderr, "open source faild: %s\n",  strerror(errno));
		exit(-1);
	}

	fd_dst = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if(fd_dst == -1)
	{
		fprintf(stderr, "open distination faild: %s\n",  strerror(errno));
                close(fd_dst);
		exit(-1);
	}


	while((read_count = read(fd_src, read_buf, BUF_SIZE)) > 0)
	{
		char* write_buf = read_buf;
		int write_count;

		while(read_count > 0)
		{
			write_count = write(fd_dst, write_buf, read_count);
            		if (write_count == -1) 
			{
                		fprintf(stderr, "cp write faild: %s", strerror(errno));
                		close(fd_src);
                		close(fd_dst);
                		exit(-1);
			}
			read_count -= write_count;
		}
	}

	if (close(fd_src) == -1) 
	{
        	fprintf(stderr, "close source faild: %s", strerror(errno));
        	exit(-1);
    	}

    	if (close(fd_dst) == -1) 
	{
        	fprintf(stderr, "close destination faild: %s", strerror(errno));
        	exit(-1);
   	 }

	return 0;	
}

