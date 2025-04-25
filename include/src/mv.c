#include "../header/utils.h"




int mv_main(int argc, char **argv) {
    
    if (argc != 3) {
        fprintf(stderr, "mv: Usage: mv source destination\n");
        return 1;
    }
    if (rename(argv[1], argv[2])) {
        perror("mv");
        return 1;
    }
    return 0;
}
