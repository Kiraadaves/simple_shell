#include "shell.h"

/**
 * str_concat- concatenate 2 strings.
 * @str1: string 1.
 * @str2: string 2, concatenated to 1
 * Return: pointer to the concatenated string.
 */
char *str_concat(char *str1, char *str2)
{
	int s1Size, s2Size, i;
	char *conStr;

	i = 0;
	s1Size = 0;
	s2Size = 0;

	if (str1 == NULL)
		str1 = "";
	if (str2 == NULL)
		str2 = "";

	while (*(str1 + s1Size))
		s1Size++;
	while (*(str2 + s2Size))
		s2Size++;
	s2Size++; /*add 1 space to print null*/

	conStr = malloc((s1Size + s2Size) * sizeof(char));
	if (conStr == NULL)
		return (NULL);

	for (i = 0; i < s1Size; i++)
		*(conStr + i) = *(str1 + i);
	for (i = s1Size; i < (s1Size + s2Size); i++)
		*(conStr + i) = *(str2 + i - s1Size);

	return (conStr);
}
