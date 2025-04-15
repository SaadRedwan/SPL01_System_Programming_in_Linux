#include "../header/utils.h"




void pwd_main() {
    char buffer[BUF_SIZE];


    if (getcwd(buffer, BUF_SIZE) != NULL) {
	printf("%s\n", buffer);
    } else {
	perror("getcwd() failed");
	exit(-1);
    }
}
