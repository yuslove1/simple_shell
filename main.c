#include "main.h"

/**
 * main - Entry
 * @ac: argument count
 * @argv: argument vector
 *
 * Return: always 0
 */
int main(int ac, char **argv)
{
	char *prompt = "$ ";
	char *lineptr;
	size_t n = 0;
	ssize_t nchars_read;

	(void)ac; (void)argv;

	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&lineptr, &n, stdin);

		if (nchars_read == -1)
		{
			printf("Exiting shell...\n");
			return (-1);
		}

		free(lineptr);
	}
	return (0);
}
