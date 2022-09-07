#include "shell.h"

/**
 * _strchr - prints from the first occurrence of a char.
 * @str: source string
 * @c: tested char
 * Return: new string.
 */
char *_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);

		else
			str++;
	}
	if (*str == c)
		return (str);
	else
		return (0);
}
