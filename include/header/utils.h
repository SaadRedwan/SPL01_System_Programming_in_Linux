#ifndef UTILS_H
#define UTILS_H




#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define BUF_SIZE 8192


void cp_main (int argc, char **argv);
void echo_main (int argc, char **argv);
char *export (char *key);
void mv_main (int argc, char **argv);
void pwd_main ();


#endif /* UTILS_H */
