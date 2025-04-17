#ifndef SRRLIB_H
#define SRRLIB_H




#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>




void femtoshell_main(void);
void parse_command(char *command, int *argc, char ***argv);
void picoshell_main(void);

#endif /* SRRLIB_H */
