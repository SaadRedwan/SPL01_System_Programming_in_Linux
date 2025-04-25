#include "./../header/utils.h"



extern Variable *variables;

int export_main(int argc, char **argv) {
    int error_occurred = 0;

    if (argc == 1) {
        // Export all variables to environment
        Variable *current = variables;
        while (current) {
            if (setenv(current->name, current->value, 1) != 0) {
                perror("setenv");
                error_occurred = 1;
            }
            current = current->next;
        }
        return error_occurred ? 1 : 0;
    }

    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        char *var_name = NULL, *var_value = NULL;

        if (strchr(arg, '=')) {
            if (split_assignment(arg, &var_name, &var_value) == -1) {
                fprintf(stderr, "export: invalid assignment '%s'\n", arg);
                error_occurred = 1;
                continue;
            }

            AddVariable(var_name, var_value); // Update shell's list
            if (setenv(var_name, var_value, 1) != 0) {
                perror("setenv");
                error_occurred = 1;
            }
            free(var_name);
            free(var_value);
        } else {
            var_name = strdup(arg);
            var_value = GetVariable(var_name);
            if (!var_value) {
                fprintf(stderr, "export: variable '%s' not found\n", var_name);
                free(var_name);
                error_occurred = 1;
                continue;
            }

            if (setenv(var_name, var_value, 1) != 0) {
                perror("setenv");
                error_occurred = 1;
                free(var_name);
                continue;
            }
            free(var_name);
        }
    }

    return error_occurred ? 1 : 0;
}
