#include "shell.h"

/**
 * print_err_exec - print errors for execute function
 * @errval: error print data
 * @ca: case number
 * @av: arguments
 */
void print_err_exec(err_t *errval, int ca, char **av)
{
	if (ca == 1)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": not found\n", 12);
	}
	else if (ca == 2)
	{
		write(STDERR_FILENO, errval->argv_0, _strlen(errval->argv_0));
		write(STDERR_FILENO, ": ", 2);
		print_err_numb(errval->e_c);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, av[0], _strlen(av[0]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
}

/**
 * exec_func - process the arguments and executes the processes
 * @av: array of pointers
 * @line: string input by user
 * @env: environments
 * @errval: error print data
 * Return: 1 on success
 */
int exec_func(char **av, char *line, char **env, err_t *errval)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(errval->argv_0);
	}
	if (child_pid == 0)
	{
		if (execve(av[0], av, env) == -1)
		{
			if ((access(av[0], F_OK) == 0) && (access(av[0], X_OK) == -1))
			{
				print_err_exec(errval, 2, av);
				_freearrp(av);
				_freearrp(env);
				free(line);
				exit(126);
			}
			else
			{
				print_err_exec(errval, 1, av);
				_freearrp(av);
				_freearrp(env);
				free(line);
				exit(127);
			}
		}
	}
	else
	{
		waitpid(child_pid, &status, WUNTRACED);
		if (WIFEXITED(status))
		{
			errval->exit_status = WEXITSTATUS(status);
		}
	}
	return (1);
}
