#include "../header/utils.h"



int cd_main(int argc, char **argv) {
    char *dir = argc == 1 ? getenv("HOME") : argv[1];
    if (!dir) {
        fprintf(stderr, "cd: HOME not set\n");
        return 1;
    }
    if (chdir(dir) != 0) {
        fprintf(stderr, "cd: %s: %s\n", dir, strerror(errno));
        return 1;
    }
    return 0;
}

