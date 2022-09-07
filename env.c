#include "shell.h"

/**
 * env_f - prints environmental variables
 * @av: array of pointers with arguments
 * @line: string input by user
 * @env: environment variable
 * @errval: error print data
 * Return: 1 on success
 */
int env_f(char **av, char *line, char ***env, err_t *errval)
{
	unsigned int i = 0;
	(void) line;

	if (av[1])
	{
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": '", 3);
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, "': No such file or directory\n", 29);
		errval->exit_status = 2;
		return (1);
	}
	while ((*env)[i] != NULL)
	{
		print_string((*env)[i]);
		print_string("\n");
		i++;
	}
	return (1);
}
