#include "shell.h"

#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define BOLD  "\x1B[1m"
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

	prompt = BLU BOLD "#Shell" RESET RED BOLD "$ " RESET;

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
