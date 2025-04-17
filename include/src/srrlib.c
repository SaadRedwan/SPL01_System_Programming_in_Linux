#include "./../header/srrlib.h"




void parse_command(char *command, int *argc, char ***argv) {

    *argc = 0;
    *argv = NULL;
    
    char *token = strtok(command, " ");
    
    while (token != NULL) {
        *argv = (char**) realloc(*argv, ((*argc) + 1) * sizeof(char *));
        (*argv)[*argc] = strdup(token);
        (*argc)++;
        token = strtok(NULL, " ");
    }
    *argv = (char**) realloc(*argv, ((*argc) + 1) * sizeof(char *));
    (*argv)[*argc] = NULL;
}

