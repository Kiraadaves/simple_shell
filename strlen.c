#include "shell.h"

/**
 * _strlen - finds the length of a given string.
 * @str: input string.
 * Return: lenght of the string.
 */
int _strlen(char *str)
{
	int length = 0;

	while (*str)
	{
		length++;
		str++;
	}
	return (length);
}
