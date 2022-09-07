#include "shell.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

/**
 * read_line - read the input line from the stream.
 * @env: enviroments.
 * @errval: error data.
 * Return: pointer to the string.
 */
char *read_line(char **env, err_t *errval)
{
	char *str = NULL;
	size_t buffsz = 0;
	ssize_t line = 1;
	char *prompt;
	char nl = '\n';

	prompt = GRN "#Shell" RESET RED "$ " RESET;

	while (1)
	{
		write(STDIN_FILENO, prompt, _strlen(prompt));
		line = getline(&str, &buffsz, stdin);
		if (line == EOF || line == -1)
		{
			write(STDIN_FILENO, &nl, 1);
			_freearrp(env);
			free(str);
			exit(errval->exit_status);
		}
		if (str == NULL || str[0] == '\n')
			continue;
		return (str);
	}
	return (NULL);
}
