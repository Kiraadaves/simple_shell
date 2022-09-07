#include "shell.h"
#define PATH_MAX 4096

/**
 * cd_home - change directory case home
 * @av: array of pointers with arguments
 * @env: environmental variables
 * @buf: buffer for the getcwd
 * @errval: error print data
 */
void cd_home(char **av, char ***env, err_t *errval, char *buf)
{
	char *directory, *old_pwd;
	int i;

	i = findenv(*env, "HOME");
	if (i == -1)
	{
		*env = setenv_cd("OLDPWD", getcwd(buf, PATH_MAX), *env);
		i = findenv(*env, "OLDPWD");
	}
	directory = _strdup(_strchr((*env)[i], '/'));
	if (directory == NULL)
	{
		print_err(errval, 1, av[1]);
		return;
	}
	old_pwd = getcwd(buf, PATH_MAX);
	chdir(directory);
	*env = setenv_cd("OLDPWD", old_pwd, *env);
	*env = setenv_cd("PWD", directory, *env);
	free(directory);
}

/**
 * cd_old - change directory case cd
 * @av: array of pointers
 * @env: environmental variables
 * @errval: error print data
 * @buf: buffer for getcwd
 */

void cd_old(char **av, char ***env, err_t *errval, char *buf)
{
	char *directory, *old_pwd;
	int i = 0;

	i = findenv(*env, "OLDPWD");
	if (i == -1)
	{
		*env = setenv_cd("OLDPWD", getcwd(buf, PATH_MAX), *env);
		i = findenv(*env, "OLDPWD");
	}
	directory = _strdup(_strchr((*env)[i], '/'));
	if (directory == NULL)
	{
		print_err(errval, 2, av[1]);
		return;
	}
	old_pwd = getcwd(buf, PATH_MAX);
	chdir(directory);
	*env = setenv_cd("OLDPWD", old_pwd, *env);
	*env = setenv_cd("PWD", directory, *env);
	print_string(directory);
	print_string("\n");
	free(directory);
}

/**
 * cd_dir - change to a given directory
 * @av: array of pointers with arguments
 * @env: environmental variables
 * @errval: error print data
 * @buf: buffer for getcwd
 */

void cd_dir(char **av, char ***env, err_t *errval, char *buf)
{
	char *old_pwd;
	int verif;

	old_pwd = getcwd(buf, PATH_MAX);
	verif = chdir(av[1]);
	if (verif == -1)
		print_err(errval, 0, av[1]);
	*env = setenv_cd("OLDPWD", old_pwd, *env);
	*env = setenv_cd("PWD", getcwd(buf, PATH_MAX), *env);
}

/**
 * change_dir - change directory
 * @av: array of pointers
 * @line: string input
 * @env: environmental variable
 * @errval: erroe print data
 * Return: 1 on success
 */

int change_dir(char **av, char *line, char ***env, err_t *errval)
{
	char *buf;
	(void) line;

	buf = malloc(PATH_MAX * sizeof(char));
	if (buf == NULL)
		return (1);
	if (!av[1])
	{
		cd_home(av, env, errval, buf);
	}
	else if (_strcmp(av[1], "-") == 0)
	{
		cd_old(av, env, errval, buf);
	}
	else if (av[1])
	{
		cd_dir(av, env, errval, buf);
	}
	free(buf);
	return (1);
}
