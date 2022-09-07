#include "shell.h"

/**
 * non_match - return 0
 * @av: array of pointers
 * @line: string input by user
 * @env: environments address
 * @errval: error print data
 * Return: 0 always
 */
int non_match(char **av, char *line, char ***env, err_t *errval)
{
	(void) av;
	(void) line;
	(void) env;
	(void) errval;

	return (0);
}

/**
 * builtins - functions that verify builtins and execute
 * @av_0: argument
 * Return: value of executed functions
 */
int (*builtins(char *av_0))(char **, char *, char ***, err_t *)
{
	built_t builts[] = {
		{"exit", exit_f},
		{"env", env_f},
		{"setenv", setenv_f},
		{"unsetenv", unsetenv_f},
		{"cd", change_dir},
		{"help", help_f},
		{NULL, non_match}
	};

	int i;
	int num_builts = 6;

	for (i = 0; i < num_builts; i++)
	{
		if (_strcmp(av_0, builts[i].bui) == 0)
		{
			return ((builts[i].f));
		}
	}
	return (builts[num_builts].f);
}
