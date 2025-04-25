#include "./../header/variables.h"

Variable *variables = NULL;

void AddVariable(const char *name, const char *value) {
    Variable *var = (Variable *)malloc(sizeof(Variable));
    if (!var) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    var->name = strdup(name);
    var->value = strdup(value);
    var->next = variables;
    variables = var;
}

char *GetVariable(const char *name) {
    Variable *current = variables;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

char *substituteString(const char *input) {
    if (!input) return NULL;
    
    size_t input_len = strlen(input);
    size_t output_cap = input_len * 2;
    char *output = (char *)malloc(output_cap);
    if (!output) return NULL;
    size_t output_len = 0;
    
    const char *p = input;
    while (*p) {
        if (*p == '$') {
            if (p[0] == '$' && (p[1] == '\0' || !isalnum(p[1]) && p[1] != '_')) {
                if (output_len + 1 >= output_cap) {
                    output_cap *= 2;
                    output = (char *)realloc(output, output_cap);
                }
                output[output_len++] = '$';
                p++;
                continue;
            }
            if (!isalnum(p[1]) && p[1] != '_') {
                if (output_len + 1 >= output_cap) {
                    output_cap *= 2;
                    output = (char *)realloc(output, output_cap);
                }
                output[output_len++] = '$';
                p++;
                continue;
            }
            
            const char *var_start = p + 1;
            const char *current = var_start;
            while (isalnum(*current) || *current == '_') current++;
            
            size_t var_len = current - var_start;
            char *var_name = (char *)malloc(var_len + 1);
            if (!var_name) {
                free(output);
                return NULL;
            }
            strncpy(var_name, var_start, var_len);
            var_name[var_len] = '\0';
            char *value = GetVariable(var_name);
            free(var_name);
            
            if (value) {
                size_t val_len = strlen(value);
                if (output_len + val_len >= output_cap) {
                    output_cap += val_len + 16;
                    output = (char *)realloc(output, output_cap);
                }
                strcpy(output + output_len, value);
                output_len += val_len;
            } else {
                p = current;
                continue;
            }
            p = current;
            continue;
        }
        
        if (output_len + 1 >= output_cap) {
            output_cap *= 2;
            output = (char *)realloc(output, output_cap);
        }
        output[output_len++] = *p++;
    }
    
    if (output_len == 0) {
        free(output);
        return strdup("");
    }
    output[output_len] = '\0';
    return output;
}

char **substituteVariables(int argc, char **argv) {
    char **new_argv = (char **)malloc((argc + 1) * sizeof(char *));
    if (!new_argv) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < argc; i++) {
        new_argv[i] = substituteString(argv[i]);
    }
    new_argv[argc] = NULL;
    return new_argv;
}

void FreeVariable(Variable *var) {
    free(var->name);
    free(var->value);
    free(var);
}

void FreeVariables() {
    Variable *current = variables;
    while (current) {
        Variable *next = current->next;
        FreeVariable(current);
        current = next;
    }
    variables = NULL;
}
