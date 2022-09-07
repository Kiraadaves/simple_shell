#include "shell.h"

/**
 * printerr_help - print errors of cd
 * @errval: error print data
 * @av: arguments
 * @i: case
 */
void printerr_help(err_t *errval, char **av, int i)
{
	if (i == 1)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": file not found or error read, write or open\n", 46);
	}
	if (i == 3)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[1], _strlen(av[1]));
		write(STDERR_FILENO, ": is not a builtin\n", 19);
	}
	if (i == 2)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": wrong syntax\n", 15);
	}
}
