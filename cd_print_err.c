#include "shell.h"

/**
 * print_err - print errors of cd
 * @errval: error print data
 * @ca: case number
 * @av_1: argument
 */
void print_err(err_t *errval, int ca, char *av_1)
{
	if (ca == 0)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": cd: can't cd to ", 18);
		write(STDERR_FILENO, av_1, _strlen(av_1));
		write(STDERR_FILENO, "\n", 1);
		errval->exit_status = 2;
	}
	else if (ca == 3)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": cd: error malloc", 18);
		errval->exit_status = 2;
	}
}
