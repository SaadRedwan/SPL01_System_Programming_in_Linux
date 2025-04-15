#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ECHO_LENGTH 4


int femtoshell_main(int argc, char *argv[]) {
    // Write your code here
    // Do not write a main() function. Instead, deal with femtoshell_main() as the main function of your program.
    
    char *command = NULL;  
    size_t len = 0;     
    ssize_t len_command;       

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
        }
        else if (strcmp(command, "exit") == 0) {  
            printf("Good Bye\n");
            if (command) { 
                free(command);
            }  
            exit(0);
        }
        else if (strncmp(command, "echo", ECHO_LENGTH) == 0) {  
            if (strlen(command) > ECHO_LENGTH) {
                printf("%s\n", command + ECHO_LENGTH + 1);  
            } else {
                printf("\n"); 
            }
        }
        else {
            printf("Invalid command\n");
        }


        if (command) {
            free(command);  
            command = NULL;  
            len = 0;      
        }
    }


    return 0;
}

