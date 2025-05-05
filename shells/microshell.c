#include "./../include/header/srrlib.h"
#include "./../include/header/utils.h"
#include "./../include/header/variables.h"


extern Variable *variables;

int main() {
    microshell_main();
    return 0;
}


void microshell_main() {
    int last_status = 0;
    char *command = NULL;
    size_t len = 0;

    while (1) {
        printf("micro shell prompt$ ");
        fflush(stdout);
        errno = 0;

        ssize_t len_command = getline(&command, &len, stdin);
        if (len_command == -1) {
            if (errno != 0) {
                fprintf(stderr, "Error occurred while reading command: %s.\n", strerror(errno));
                free(command);
                exit(1);
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
        for (int i = 0; i < cmd_argc; i++) free(cmd_argv[i]);
        free(cmd_argv);
        cmd_argv = substituted_argv;

        int stdin_save = dup(STDIN_FILENO);
        int stdout_save = dup(STDOUT_FILENO);
        int stderr_save = dup(STDERR_FILENO);
        int fd_in = -1, fd_out = -1, fd_err = -1;
        int redirect_failed = 0;

       
        int new_argc = 0;
        char **new_argv = (char **)malloc((cmd_argc + 1) * sizeof(char *));
        if (!new_argv) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < cmd_argc && !redirect_failed; i++) {
            if (i < cmd_argc && strcmp(cmd_argv[i], "<") == 0) {
                if (i + 1 >= cmd_argc || cmd_argv[i + 1] == NULL) {
                    fprintf(stderr, "Missing filename after '<'\n");
                    redirect_failed = 1;
                } else {
                    fd_in = open(cmd_argv[i + 1], O_RDONLY);
                    if (fd_in == -1) {
                        if (errno == ENOENT) {
                            fprintf(stderr, "cannot access %s: No such file or directory\n", cmd_argv[i + 1]);
                        } else {
                            fprintf(stderr, "%s: %s\n", cmd_argv[i + 1], strerror(errno));
                        }
                        redirect_failed = 1;
                    } else if (dup2(fd_in, STDIN_FILENO) == -1) {
                        perror("dup2 stdin");
                        redirect_failed = 1;
                    } else {
                        i++;
                    }
                }
            } else if (i < cmd_argc && strcmp(cmd_argv[i], ">") == 0) {
                if (i + 1 >= cmd_argc || cmd_argv[i + 1] == NULL) {
                    fprintf(stderr, "Missing filename after '>'\n");
                    redirect_failed = 1;
                } else {
                    fd_out = open(cmd_argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd_out == -1) {
                        fprintf(stderr, "%s: %s\n", cmd_argv[i + 1], strerror(errno));
                        redirect_failed = 1;
                    } else if (dup2(fd_out, STDOUT_FILENO) == -1) {
                        perror("dup2 stdout");
                        redirect_failed = 1;
                    } else {
                        i++;
                    }
                }
            } else if (i < cmd_argc && strcmp(cmd_argv[i], "2>") == 0) {
                if (i + 1 >= cmd_argc || cmd_argv[i + 1] == NULL) {
                    fprintf(stderr, "Missing filename after '2>'\n");
                    redirect_failed = 1;
                } else {
                    fd_err = open(cmd_argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
                    if (fd_err == -1) {
                        fprintf(stderr, "%s: %s\n", cmd_argv[i + 1], strerror(errno));
                        redirect_failed = 1;
                    } else if (dup2(fd_err, STDERR_FILENO) == -1) {
                        perror("dup2 stderr");
                        redirect_failed = 1;
                    } else {
                        i++;
                    }
                }
            } else {
                new_argv[new_argc++] = cmd_argv[i];
            }
        }

        new_argv[new_argc] = NULL;

        if (redirect_failed) {
            last_status = 1;

            dup2(stdin_save, STDIN_FILENO);
            dup2(stdout_save, STDOUT_FILENO);
            dup2(stderr_save, STDERR_FILENO);

            if (fd_in != -1) close(fd_in);
            if (fd_out != -1) close(fd_out);
            if (fd_err != -1) close(fd_err);
            close(stdin_save);
            close(stdout_save);
            close(stderr_save);

            free(new_argv);
            for (int i = 0; i < cmd_argc; i++) free(cmd_argv[i]);
            free(cmd_argv);
            free(command);
            command = NULL;

            continue;  
        }

        if (new_argc == 0) {
            free(new_argv);
            for (int i = 0; i < cmd_argc; i++) free(cmd_argv[i]);
            free(cmd_argv);
            free(command);
            command = NULL;
            continue;
        }

        
        if (strcmp(new_argv[0], "exit") == 0) {
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
    	} else if (strcmp(new_argv[0], "export") == 0) {
            if (new_argc != 2) {
                fprintf(stderr, "export: Usage: export variable\n");
                last_status = 1;
            } else {
                char *var_name = new_argv[1];
                char *value = GetVariable(var_name);
                if (value) {
                    if (setenv(var_name, value, 1) != 0) {
                        perror("setenv");
                        last_status = 1;
                    } else {
                        last_status = 0;
                    }
                } else {
                    fprintf(stderr, "export: variable '%s' not found\n", var_name);
                    last_status = 1;
                }
            }
        } else {
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork");
                last_status = 1;
            } else if (pid == 0) {
                execvp(new_argv[0], new_argv);
                fprintf(stderr, "%s: command not found\n", new_argv[0]);
                exit(EXIT_FAILURE);
            } else {
                int status;
                waitpid(pid, &status, 0);
                last_status = WEXITSTATUS(status);
            }
        }

        
        dup2(stdin_save, STDIN_FILENO);
        dup2(stdout_save, STDOUT_FILENO);
        dup2(stderr_save, STDERR_FILENO);
        close(stdin_save);
        close(stdout_save);
        close(stderr_save);
        if (fd_in != -1) close(fd_in);
        if (fd_out != -1) close(fd_out);
        if (fd_err != -1) close(fd_err);

     
        free(new_argv);
        for (int i = 0; i < cmd_argc; i++) {
            free(cmd_argv[i]);
        }
        free(cmd_argv);
        free(command);
        command = NULL;
    }

    FreeVariables();
}
