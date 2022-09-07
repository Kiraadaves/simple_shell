#include "shell.h"

/**
 * get_print_file - reads and prints file info
 * @file_from: file name
 * @errval: error print values
 * Return: 0 on success, otherwise, -1
 */
int get_print_file(char *file_from, err_t *errval)
{
	char buf[1024];
	int fd, letter_co;
	ssize_t buf_sz = 1024;

	fd = open(file_from, O_RDONLY);
	if (fd == -1)
		return (-1);
	while (buf_sz == 1024)
	{
		buf_sz = read(fd, buf, 1024);
		if (buf_sz == -1)
			return (-1);
		letter_co = write(STDOUT_FILENO, buf, buf_sz);
		if (letter_co == -1)
			return (-1);
	}
	if (close(fd) == -1)
		return (-1);
	errval->exit_status = 0;
	return (0);
}

/**
 * check_func_sintax - verifies arguments
 * @av: array of pointers
 * @errval: error print data
 * Return: 1 if it exists, else -1
 */
int check_func_sintax(char **av, err_t *errval)
{
	if (!av[2])
	{
		if (_strcmp(av[1], "exit") == 0)
			return (0);
		if (_strcmp(av[1], "env") == 0)
			return (0);
		if (_strcmp(av[1], "setenv") == 0)
			return (0);
		if (_strcmp(av[1], "unsetenv") == 0)
			return (0);
		if (_strcmp(av[1], "cd") == 0)
			return (0);
		if (_strcmp(av[1], "help") == 0)
			return (0);
	}
	else
	{
		printerr_help(errval, av, 2);
		errval->exit_status = 2;
	}
	printerr_help(errval, av, 3);
	errval->exit_status = 2;
	return (-1);
}

/**
 * g_dir get executiom '_' path
 * @av: array of pointers
 * @env: environment varaiables
 * @ev: error data
 * @file_f: pointer to string address.
 * @path_val: execute shell path
 * Return: resulting path pointer
 */
char *g_dir(char **av, char **env, err_t *ev, char **file_f, char **path_val)
{
	int i, verif;

	verif = check_func_sintax(av, ev);
	if (verif == -1)
		return (NULL);
	*file_f = str_concat(av[1], "_file");
	i = findenv(env, "_");
	if (i == -1)
	{
		if (get_print_file(*file_f, ev) == -1)
		{
			printerr_help(ev, av, 1);
			ev->exit_status = 2, free(*file_f);
			return (NULL);
		}
	}
	*path_val = _strdup(_strchr(env[i], '=') + 1);
	if (*path_val == NULL)
	{
		if (get_print_file(*file_f, ev) == -1)
		{
			printerr_help(ev, av, 1), ev->exit_status = 2;
			free(*file_f), free(*path_val);
			return (NULL);
		}
	}
	return (*path_val);
}

/**
 * modif_path - modify execution path for concatenation
 * @path_values: path
 */
void modif_path(char **path_values)
{
	char *aux;

	rev_string(*path_values);
	aux = _strdup(_strchr(*path_values, '/'));
	rev_string(aux);
	free(*path_values);
	*path_values = aux;
}

/**
 * help_f - exit built-in
 * @av: array of pointers
 * @line: string input by user
 * @env: environment variables
 * @errval: error print values
 * Return: 1 if executed
 */
int help_f(char **av, char *line, char ***env, err_t *errval)
{
	char *file_from = NULL, *path_values, *file;
	int verif;
	(void) line;

	path_values = g_dir(av, *env, errval, &file_from, &path_values);
	if (path_values == NULL)
	{
		return (1);
	}
	modif_path(&path_values);
	file = str_concat(path_values, file_from);
	verif = get_print_file(file, errval);
	if (verif == -1)
	{
		printerr_help(errval, av, 1), errval->exit_status = 2;
		free(file_from), free(path_values), free(file);
		return (1);
	}
	free(file_from), free(path_values), free(file);
	return (1);
}
