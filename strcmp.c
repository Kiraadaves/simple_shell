#include "shell.h"

/**
 * _strcmp - compare 2 strings.
 * @str1: string to be compared.
 * @str2: string for comparation.
 * Return: 0 on sucess otherwise difference
 */
int _strcmp(char *str1, char *str2)
{
	while ((*str1 && *str2) && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 - *str2);
}
