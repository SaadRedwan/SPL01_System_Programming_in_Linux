#ifndef UTILS_H
#define UTILS_H




#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define BUF_SIZE 8192


int cd_main(int argc, char **argv);
int cp_main (int argc, char **argv);
void echo_main (int argc, char **argv);
char *export (char *key);
int mv_main (int argc, char **argv);
int pwd_main ();


#endif /* UTILS_H */
