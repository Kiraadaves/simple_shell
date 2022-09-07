#include "shell.h"

/**
 * change_to_space - change delims to spaces.
 * @line: given string.
 */
void change_to_space(char *line)
{
	int del, li;
	char delim[] = "\n\t\r\a";

	for (del = 0; delim[del]; del++)
	{
		for (li = 0; line[li]; li++)
			if (delim[del] == line[li])
				line[li] = ' ';
	}
}

/**
 * cwords - count number of words in a given string.
 * @str: given string.
 * @l: lenght of string.
 * Return: number of words.
 */
int cwords(char *str, int l)
{
	int i, count_w = 0;

	for (i = 0; i < l; i++)
	{
		if (str[i] != ' ')
		{
			for (; str[i] != ' '; i++)
				;
			count_w++;
		}
	}
	return (count_w);
}

/**
 * split_line - separate the string to a vector of arguments av.
 * @line: pointer to the string.
 * Return: pointer to the new array of string pointers.
 */
char **split_line(char *line)
{
	char delim[] = " ";
	char *token;
	char **av;

	/*Remember count_words to 0 for the real case*/
	int count_words, count_buff = 0, len;

	change_to_space(line);
	len = _strlen(line);
	count_words = cwords(line, len);
	if (count_words == 0)
		return (NULL);

	/*Get the 1st token*/
	token = _strtok(line, delim);
	av = _calloc((count_words + 1), sizeof(char *));
	if (av == NULL)
		return (NULL);

	/*Get other tokens*/
	while (token != NULL)
	{
		av[count_buff] = _strdup(token);
		if (av[count_buff] == NULL)
		{
			_freearrp(av);
			return (NULL);
		}
		count_buff++;
		token = _strtok(NULL, delim);
	}
	/*Finish the **array with NULL*/
	av[count_buff] = NULL;

	return (av);
}
