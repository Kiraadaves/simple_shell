#include "shell.h"

/**
 * rev_string - function that reverses a string.
 * @str: input string.
 */
void rev_string(char *str)
{
	int length = 0, i;
	char temp;

	/*count the lenght of the string*/
	while (*(str + length) != '\0')
	{
		length++;
	}
	for (i = 0; i < (length / 2); i++)
	{
		temp = *(str + i);
		*(str + i) = *(str + length - i - 1);
		*(str + length - i - 1) = temp;
	}
}
