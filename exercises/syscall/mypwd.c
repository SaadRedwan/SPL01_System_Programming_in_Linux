#include <stdio.h>   
#include <stdlib.h>  
#include <unistd.h>
#include <limits.h>  



int main() {
	
	char buffer[PATH_MAX];


    	if (getcwd(buffer, PATH_MAX) != NULL) 
	{
        	printf("%s\n", buffer);
    	}
    	else 
    	{
		perror("getcwd() failed"); 
       		exit(-1);
    	}

    	return 0;
}
