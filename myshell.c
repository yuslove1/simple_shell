#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(void)
{
	char buffer[BUFFER_SIZE];
	int status;

	while (1) {
		/*Display prompt*/
		printf("$ ");
		fflush(stdout);

		/* Read user input*/
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) 
		{
		/* Handle end of file (Ctrl+D)*/
			if (feof(stdin)) 
			{
				break;
			}
            /*Handle error*/
			perror("fgets");
			exit(EXIT_FAILURE);
		}

		/*Remove trailing newline character*/

		buffer[strcspn(buffer, "\n")] = '\0';
		/* Tokenize command line into arguments*/
		char *args[BUFFER_SIZE];
		char *token = strtok(buffer, " ");
		int i = 0;
		while (token != NULL)
		{
			args[i] = token;
			i++;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;
        	/* Check if command is exit*/
		if (strcmp(args[0], "exit") == 0)
		{
			/*Exit shell*/
			break;
		}
		/* Check if command is env*/
		if (strcmp(args[0], "env") == 0)
		{
			/*Print current environment*/
			char **env = environ;
			while (*env != NULL) 
			{
				printf("%s\n", *env);
				env++;
			}
			continue;
		}
		/* Check if command exists*/
		char path[BUFFER_SIZE];
		int command_found = 0;
		char *path_env = getenv("PATH");
		token = strtok(path_env, ":");
		while (token != NULL) 
		{
			sprintf(path, "%s/%s", token, args[0]);
			if (access(path, F_OK) != -1) 
			{
				command_found = 1;
				break;
			}
			token = strtok(NULL, ":");
		}
		if (command_found) 
		{
            /* Fork and execute command*/
			pid_t pid = fork();
			if (pid == -1) 
			{
                /* Handle error */
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0) 
			{
                	/* Child process */
			int result = execv(path, args);
			if (result == -1) 
				{
                    /* Handle error*/
				perror("execv");
				exit(EXIT_FAILURE);
				}
			}
			else
			{
				/* Parent process */
				do
				{
                    /* Wait for child process to terminate */
				pid_t wpid = waitpid(pid, &status, WUNTRACED);
				if (wpid == -1) 
				{
                        /* Handle error */
				perror("waitpidexit(EXIT_FAILURE);
				exit(EXIT_FAILURE);
				}
				while (!WIFEXITED(status) && !WIFSIGNALED(status));
				}
				}
				else
				{
            /* Command not found */
				printf("%s: command not found\n", args[0]);
				}
				}
				return 0;
				}
