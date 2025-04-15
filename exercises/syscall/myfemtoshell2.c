#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#define COMMAND_MAX (PATH_MAX + PATH_MAX + PATH_MAX)
#define EXIT_LENGTH 4
#define ECHO_LENGTH 4

// Function to flush leftover input
void flush_input() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
}

int main()
{
    char command[COMMAND_MAX];
    char *retResult;

    while (1)
    {
        fprintf(stdout, "srr femto shell prompt$ ");
        retResult = fgets(command, COMMAND_MAX, stdin);

        if (retResult == NULL) 
	{
            break; 
        }

        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') 
        {
            command[len - 1] = '\0';
        } 
        else 
        {
            flush_input();
        }

        if (strlen(command) == 0) 
        {  
            continue;
        }
        else if (strcmp(command, "exit") == 0) 
        {  
            fprintf(stdout, "Good Bye\n");
            exit(0);
        }
        else if (strncmp(command, "echo", ECHO_LENGTH) == 0) 
        {  
            if (strlen(command) > ECHO_LENGTH) 
            {
                fprintf(stdout, "%s\n", command + ECHO_LENGTH + 1);
            } 
            else 
            {
                fprintf(stdout, "\n"); 
            }
        }
        else
       	{
            fprintf(stdout, "Invalid command\n");
        }
    }

    return 0;
}
