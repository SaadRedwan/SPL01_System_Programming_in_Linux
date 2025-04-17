#include "./../include/header/srrlib.h"




int main() {
    femtoshell_main();	   
    return 0;
}

void femtoshell_main() {
	char *command = NULL;  
    	size_t len = 0;     
    	ssize_t len_command;       
    	int argc;
    	char **argv;

    	while (1) {
        	
        	printf("srr femto shell prompt$ ");
                len_command = getline(&command, &len, stdin);

                if (len_command == -1) {
                        if (errno != 0) {
                                fprintf(stderr, "Error occurred while reading command: %s.\n", strerror(errno));
                                free(command);
                                exit(-1);
                        } else {  /*to avoid memory leak as getline allocate mem even if EOF occoured */
                                free(command);
                                return;
                        }
                } else {
                        command[len_command - 1] = '\0';
                }

        	if (strlen(command) == 0) {  
            		continue;
        	} else {
            		parse_command(command, &argc, &argv);
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
}
