#include "shell.h"
/**
 * _freeArrPtr - frees completely an array of pointers.
 * @av: array of pointers
 * Return: Always 0.
 */
void _freeArrPtr(char **av)
{
	int i;

	for (i = 0; av[i]; i++)
	{
		free(av[i]);
	}
	free(av[i]);
	free(av);
}