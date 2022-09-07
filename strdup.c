#include "shell.h"

/**
 * _strdup - create new space in memory that contains copy of a given string
 * @str: given string.
 * Return: Pointer to allocated memory.
 */
char *_strdup(char *str)
{
	char *dupl;
	unsigned int i, cp;

	if (str == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		;

	dupl = _calloc((i + 1), sizeof(char));

	if (dupl == NULL)
		return (NULL);

	for (cp = 0; cp <= i; cp++)
		dupl[cp] = str[cp];

	return (dupl);
}
