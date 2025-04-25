#include "./../include/header/srrlib.h"
#include "./../include/header/utils.h"
#include "./../include/header/variables.h"


extern Variable *variables;

int main() {
    nanoshell_main();
    return 0;
}

void nanoshell_main() {
    int last_status = 0;
    char *command = NULL;
    size_t len = 0;
    
    while (1) {
        printf("srr pico shell prompt$ ");
        fflush(stdout);
        errno = 0;
        
        ssize_t len_command = getline(&command, &len, stdin);
        if (len_command == -1) {
            if (errno != 0) {
                fprintf(stderr, "Error reading command: %s\n", strerror(errno));
                free(command);
                exit(EXIT_FAILURE);
            } else {
                free(command);
                exit(last_status);
            }
        }
        command[len_command - 1] = '\0';
        
        if (strlen(command) == 0) {
            free(command);
            command = NULL;
            continue;
        }
        
        if (is_assignment(command)) {
            process_assignment(command);
            free(command);
            command = NULL;
            continue;
        }
        
        int cmd_argc = 0;
        char **cmd_argv = NULL;
        parse_command(command, &cmd_argc, &cmd_argv);
        
        if (cmd_argc == 0) {
            free(cmd_argv);
            free(command);
            command = NULL;
            continue;
        }
        
        char **substituted_argv = substituteVariables(cmd_argc, cmd_argv);
        free(cmd_argv);
        cmd_argv = substituted_argv;
        
        if (strcmp(cmd_argv[0], "exit") == 0) {
            printf("Good Bye\n");
            exit(last_status);
        } else if (strcmp(cmd_argv[0], "cd") == 0) {
            last_status = cd_main(cmd_argc, cmd_argv);
        } else if (strcmp(cmd_argv[0], "cp") == 0) {
		cp_main(cmd_argc, cmd_argv);
		last_status = 0;
	} else if (strcmp(cmd_argv[0], "echo") == 0) {
            echo_main(cmd_argc, cmd_argv);
            last_status = 0;
        } else if (strcmp(cmd_argv[0], "mv") == 0) {
		last_status = mv_main(cmd_argc, cmd_argv);
    	} else if (strcmp(cmd_argv[0], "pwd") == 0) {
		pwd_main();
		last_status = 0;
    	} else if (strcmp(cmd_argv[0], "export") == 0) {
            last_status = export_main(cmd_argc, cmd_argv);
        } else {
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                last_status = 1;
            } else if (pid == 0) {
                execvp(cmd_argv[0], cmd_argv);
                 fprintf(stderr, "%s: command not found\n", cmd_argv[0]);
                exit(EXIT_FAILURE);
            } else {
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    perror("waitpid");
                    last_status = 1;
                } else {
                    last_status = WEXITSTATUS(status);
                }
            }
        }
        
        // Cleanup
        for (int i = 0; i < cmd_argc; i++) {
            free(cmd_argv[i]);
        }
        free(cmd_argv);
        free(command);
        command = NULL;
    }

    FreeVariables();
    //return last_status;
}
