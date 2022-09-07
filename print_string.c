#include "shell.h"
/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * print_string - function that prints stings.
 * @str: pointer to string.
 * Return: length of string.
 */
int print_string(char *str)
{
	char empty[] = "(null)";
	int i, length;

	if (str == NULL)
	{
		for (i = 0; empty[i]; i++)
			_putchar(empty[i]);
		return (6);
	}
	for (i = 0; str[i]; i++)
		_putchar(str[i]);
	length = _strlen(str);
	return (length);
}
