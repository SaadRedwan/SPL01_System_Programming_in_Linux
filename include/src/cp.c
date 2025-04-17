#include "../header/utils.h"




int cp_main(int argc, char **argv) {

    if (argc != 3) {
	fprintf(stderr, "Usage %s source destination\n", argv[0]);
	return -1;
    }

    const char *src = argv[1];
    const char *dst = argv[2];
    int fd_src, fd_dst;
    char read_buf[BUF_SIZE];
    ssize_t read_count;


    fd_src = open(src, O_RDONLY);

    if (fd_src == -1) {
	fprintf(stderr, "open source faild: %s\n", strerror(errno));
	return -1;
    }

    fd_dst = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dst == -1) {
	fprintf(stderr, "open distination faild: %s\n", strerror(errno));
	close(fd_dst);
	return -1;
    }


    while ((read_count = read(fd_src, read_buf, BUF_SIZE)) > 0) {
	char* write_buf = read_buf;
	int write_count;
	char *ptr = read_buf;
    	ssize_t remaining = read_count;
    	
    	while (remaining > 0) {
        	ssize_t write_count = write(fd_dst, ptr, remaining);
        	if (write_count == -1) {
            		fprintf(stderr, "cp write failed: %s\n", strerror(errno));
            		close(fd_src);
            		close(fd_dst);
            		return -1;
        	}
        	ptr += write_count;
        	remaining -= write_count;
    	}
    }

    if (close(fd_src) == -1) {
	fprintf(stderr, "close source faild: %s", strerror(errno));
	return -1;
    }

    if (close(fd_dst) == -1) {
	fprintf(stderr, "close destination faild: %s", strerror(errno));
	return -1;
    }
    return 0;
}
