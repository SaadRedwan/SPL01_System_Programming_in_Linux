#ifndef SRRLIB_H
#define SRRLIB_H




#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "./../header/variables.h"

#define INIT_CAPACITY 8



int is_assignment(const char *command);
int split_assignment(const char *input, char **name, char **value);
void parse_command(char *command, int *argc, char ***argv);
void process_assignment(const char *command); 


void femtoshell_main(void);
void picoshell_main(void);
void nanoshell_main(void);

#endif /* SRRLIB_H */
