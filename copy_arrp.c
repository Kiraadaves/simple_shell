#include "shell.h"

/**
 * _cpyarrp - create a copy of char data structure
 * @arrp: input data structure
 * Return: pointer to created data struct
 */
char **_cpyarrp(char **arrp)
{
	int i, j;
	char **index;

	if (arrp == NULL)
		print_string("error env not found");
	for (i = 0; arrp[i] != NULL; i++)
		;
	index = malloc((i + 1) * sizeof(char *));
	if (index == NULL)
	{
		print_string("cpy env failed");
		return (NULL);
	}
	for (j = 0; j < i; j++)
	{
		index[j] = _strdup(arrp[j]);
	}
	index[j] = NULL;
	return (index);
}
