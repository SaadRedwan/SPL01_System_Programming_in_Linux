#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void print_wrapper(void)
{
	if (write(1, "Hello Linux\n", strlen("Hello Linux\n")) < 0);
        	exit(-1);
}

int main()
{
        //printf("Hello Linux\n");
	print_wrapper();
	print_wrapper();
	print_wrapper();
	print_wrapper();
	print_wrapper();
	print_wrapper();
	return 0;
}
