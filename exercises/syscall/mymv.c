#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int mymv(int argc, char** argv);

int main(int argc, char** argv)
{
	
	mymv(argc, argv);	
	
	return 0;
}



int mymv(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr, "Usage: mv source distination\n");
        exit(-1);
    }

    if (rename(argv[1], argv[2]) < 0) {
        if (errno == ENOENT) {
            fprintf(stderr, "No such file or directory: %s\n", argv[1]);
            exit(-1);
        }
    }
    
    return 0;	
}
