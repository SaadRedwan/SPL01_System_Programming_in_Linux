#ifndef UTILS_H
#define UTILS_H




#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "./../header/variables.h"
#include "./../header/srrlib.h"


#define BUF_SIZE 8192


int cd_main(int argc, char **argv);
void cp_main (int argc, char **argv);
void echo_main (int argc, char **argv);
int export_main(int argc, char **argv);
int mv_main (int argc, char **argv);
void pwd_main ();


#endif /* UTILS_H */
