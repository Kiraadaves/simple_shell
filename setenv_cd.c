#include "shell.h"

/**
 * setenv_cd - initialize a new environment variable or modify existing one
 * @name_var: variable name
 * @cont_var: variable value
 * @env: environment variables
 * Return: pointer to new environment data struct
 */

char **setenv_cd(char *name_var, char *cont_var, char **env)
{
	int verif, i, j;
	char delim[] = "=";
	char *mod_env, *aux, *new_evar;
	char **new_env;

	verif = findenv(env, name_var);
	if (verif == -1)
	{
		for (i = 0; env[i] != NULL; i++)
			;
		aux = str_concat("=", cont_var);
		new_evar = str_concat(name_var, aux);
		new_env = malloc((i + 2) * sizeof(char *));
		if (new_env == NULL)
		{
			free(aux);
			free(new_evar);
			return (NULL);
		}
		for (j = 0; j < i; j++)
			new_env[j] = _strdup(env[j]);
		new_env[j] = new_evar;
		new_env[j + 1] = NULL;
		free(aux);
		_freearrp(env);
		return (new_env);
	}
	else
	{
		aux = str_concat(delim, cont_var);
		mod_env = str_concat(name_var, aux);
		free(env[verif]);
		env[verif] = mod_env;
		free(aux);
		return (env);
	}
}
