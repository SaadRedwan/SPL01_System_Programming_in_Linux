#include "../header/utils.h"




void pwd_main() {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("pwd");
        exit(127);
    }
    printf("%s\n", cwd);
    free(cwd);
}
