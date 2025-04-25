#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Variable {
    char *name;
    char *value;
    struct Variable *next;
} Variable;

void AddVariable(const char *name, const char *value);
char *GetVariable(const char *name);
char *substituteString(const char *input);
char **substituteVariables(int argc, char **argv);
void FreeVariable(Variable *var);
void FreeVariables();

#endif
