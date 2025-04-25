#include "./../header/srrlib.h"


// Assignment validation
int is_assignment(const char *command) {
    const char *p = command;
    int has_equal = 0;
    while (*p) {
        if (*p == '=') {
            has_equal ^= 1;
            if (has_equal < 0 || has_equal > 1) return 0;
        }
        if (*p == ' ') return 0;
        p++;
    }
    return has_equal == 1 && strchr(command, '=') != command && *(strchr(command, '=') + 1);
}

// Split "VARIABLE=VALUE" into name and value
int split_assignment(const char *input, char **name, char **value) {
    const char *eq = strchr(input, '=');
    if (!eq) return -1;
    size_t name_len = eq - input;
    *name = strndup(input, name_len);
    *value = strdup(eq + 1);
    return 0;
}

// Process variable assignments
void process_assignment(const char *command) {
    char *equal = strchr((char *)command, '=');
    if (!equal || !equal[1] || equal == command) {
        fprintf(stderr, "Invalid assignment\n");
        return;
    }
    size_t name_len = equal - command;
    char *var_name = (char *)malloc(name_len + 1);
    if (!var_name) {
        perror("malloc");
        return;
    }
    strncpy(var_name, command, name_len);
    var_name[name_len] = '\0';
    char *var_value = strdup(equal + 1);
    AddVariable(var_name, var_value);
    free(var_name);
    free(var_value);
}

void parse_command(char *command, int *argc, char ***argv) {
    *argc = 0;
    size_t capacity = INIT_CAPACITY;
    *argv = (char **)malloc(capacity * sizeof(char *));
    if (!*argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    char *token = strtok(command, " ");
    while (token) {
        if (*argc >= capacity) {
            capacity *= 2;
            *argv = (char **)realloc(*argv, capacity * sizeof(char *));
            if (!*argv) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        (*argv)[*argc] = strdup(token);
        (*argc)++;
        token = strtok(NULL, " ");
    }
    
    if (*argc < capacity) {
        (*argv)[*argc] = NULL;
    } else {
        capacity++;
        *argv = (char **)realloc(*argv, capacity * sizeof(char *));
        (*argv)[*argc] = NULL;
    }
}


