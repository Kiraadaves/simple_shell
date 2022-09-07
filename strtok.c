#include "shell.h"
/**
 * _strspn - Write a function that gets the length of a prefix substring
 * @str: input string.
 * @accept: character to be compared.
 * Return: number of bytes.
 */
unsigned int _strspn(char *str, char *accept)
{
	unsigned int i, j, count = 0;

	for (i = 0; str[i]; i++)
	{
		for (j = 0, count = 0; accept[j]; j++)
		{
			if (str[i] == accept[j])
				count++;
		}
		if (count == 0)
			return (i);
	}
	return (i);
}
/**
 * _strcspn - Write a function that gets the number the characters until
 * the ocurrence
 * @str: input string.
 * @reject: character to be compared.
 * Return: number of char.
 */
unsigned int _strcspn(char *str, char *reject)
{
	unsigned int i, j = 0;

	for (i = 0; str[i]; i++)
		for (j = 0; reject[j]; j++)
			if (str[i] == reject[j])
				return (i);
	return (i);
}
/**
 * _strtok_r - gets the token from a given pointer
 * @str: input string.
 * @delim: the delimiter
 * @save_ptr: previous saved pointer.
 * Return: pointer to extracted token.
 */
char *_strtok_r(char *str, char *delim, char **save_ptr)
{
	char *end;
	unsigned int n;
	/*2nd or more call case*/
	if (str == NULL)
		str = *save_ptr;
	/*General case to finish the function*/
	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}

	/*Locate the pointer str at the beginning of token*/
	n = _strspn(str, delim);
	if (n > 0)
		str = str + n;
	if (*str == '\0')
	{
		*save_ptr = str;
		return (NULL);
	}

	/*Locate the last character of token*/
	n = _strcspn(str, delim);
	if (n > 0)
		end = str + n;
	if (*end == '\0')
	{
		*save_ptr = end;
		return (str);
	}

	/*Once get the token, change the delim character by null and save the*/
	/*beggining of the new token*/
	*end = '\0';
	*save_ptr = end + 1;
	return (str);
}
/**
 * _strtok - gets the token of a given string
 * @str: input string.
 * @delim: the delimiter
 * Return: pointer to extracted token.
 */
char *_strtok(char *str, char *delim)
{
	static char *saved_ptr;

	return (_strtok_r(str, delim, &saved_ptr));
}
