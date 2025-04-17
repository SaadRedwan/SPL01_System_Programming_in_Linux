#include "./../include/header/srrlib.h"
#include "./../include/header/utils.h"




int main() {
    picoshell_main();
    return 0;
}

void picoshell_main() {
    
    char *command = NULL;
    size_t len = 0;
    ssize_t len_command;
    int argc;
    char **argv;

    while (1) {
	printf("srr pico shell prompt$ ");
	len_command = getline(&command, &len, stdin);

	if (len_command == -1) {
	    if (errno != 0) {
		fprintf(stderr,
			"Error occurred while reading command: %s.\n",
			strerror(errno));
		free(command);
		exit(-1);
	    } else {
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
	    } else if (strcmp(argv[0], "cd") == 0) {
		    cd_main(argc, argv);
	    } else if (strcmp(argv[0], "cp") == 0) {
		cp_main(argc, argv);
	    } else if (strcmp(argv[0], "echo") == 0) {
		echo_main(argc, argv);
	    } else if (strcmp(argv[0], "mv") == 0) {
		mv_main(argc, argv);
	    } else if (strcmp(argv[0], "pwd") == 0) {
		pwd_main();
	    } else {
		id_t pid = fork();
		
		if (pid < 0) {
			printf("frok faild: can't create the process\n");
	    	} else if (pid > 0) {	
		    int status;
		    wait(&status);
		    WEXITSTATUS(status);
		} else if (pid == 0) {

		    execvp(argv[0], argv);

		    printf("execvp faild: %s : invalid command\n", argv[0]);
		    exit(-1);
		}
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
