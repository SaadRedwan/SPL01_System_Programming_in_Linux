#include "../header/utils.h"




void mv_main(int argc, char **argv) {

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
}
