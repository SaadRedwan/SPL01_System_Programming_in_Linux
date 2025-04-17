#include "../header/utils.h"




int pwd_main() {
    char *cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("pwd");
        return -1;
    }
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}
