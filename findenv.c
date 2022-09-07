#include "shell.h"

/**
 * findenv - look for specifics environments variables
 * @env: environments
 * @cmp_val: looked variable
 * Return: index number if found, else -1
 */
int findenv(char **env, char *cmp_val)
{
	int i, num_env;
	char delim[] = "=";
	char *token, *cp_tok, *cp_env;

	for (num_env = 0; env[num_env] != NULL; num_env++)
		;
	for (i = 0; env[i] != NULL; i++)
	{
		cp_env = _strdup(env[i]);
		token = _strtok(cp_env, delim);
		cp_tok = _strdup(token);
		if (_strcmp(cp_tok, cmp_val) == 0)
		{
			free(cp_tok);
			free(cp_env);
			return (i);
		}
		free(cp_tok);
		free(cp_env);
	}
	if (i == num_env)
	{
		return (-1);
	}
	return (0);
}
