#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ECHO_LENGTH 4

int femtoshell_main(void);
void get_args(char *command, int *argc, char ***argv); 

int main() {
    femtoshell_main();	   
    return 0;
}

int femtoshell_main() {
	char *command = NULL;  
    	size_t len = 0;     
    	ssize_t len_command;       
    	int argc;
    	char **argv;

    	while (1) {
        	printf("srr femto shell prompt$ ");
        	len_command = getline(&command, &len, stdin);  

        	if (len_command == -1) {  
            		if (command) { 
                		free(command);
            		}
            		break;
        	}

        	if (len_command > 0 && command[len_command - 1] == '\n') {
            		command[len_command - 1] = '\0';
        	}

        	if (strlen(command) == 0) {  
            		continue;
        	} else {
            		get_args(command, &argc, &argv);
			if (strcmp(argv[0], "exit") == 0) {  
                		printf("Good Bye\n");
                		free(command);
                		for (int i = 0; i < argc; i++) {
                    			free(argv[i]);
                		}
                		free(argv);
                		exit(0);
            		} else if (strcmp(argv[0], "echo") == 0) {  
                		for (int i = 1; i < argc; i++) {
                    			printf("%s", argv[i]);
					if(i != (argc-1)) {
						printf(" ");
					}
                		}
				printf("\n");	
            		} else {
                		printf("Invalid command\n");
            		}

            // Free argv and its elements
            for (int i = 0; i < argc; i++) {
                free(argv[i]);
            }
            free(argv);
        }
        free(command);
        command = NULL;
        len = 0;
    }
    return 0;
}

void get_args(char *command, int *argc, char ***argv) {
    	
	*argc = 0;
    	*argv = (char**)malloc((strlen(command) / 2 + 2) * sizeof(char *));

    	if (strlen(command) < 1) {
        	return;
    	}

    	char *token = strtok(command, " ");
   

    	while (token != NULL) {
        	(*argv)[(*argc)] = strdup(token);
	       	token = strtok(NULL, " ");
		(*argc)++;
    	}
}
