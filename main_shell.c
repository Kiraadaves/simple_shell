#include "shell.h"

/**
 * main - main function that accepts input
 * @argc: command line argument count
 * @agrv: command line vector count
 * Return: 0 on success
 */

int main(int argc __attribute__((unused)), char **argv)
{
	char *prompt = "#shell$ ";
	char *string = NULL;
	size_t n = 0;
	ssize_t line;
	(void)argv;

	/*signal(SIGINT, ctrl_C);*/

	while (1)
	{

		write(STDOUT_FILENO, prompt, 9);
		line = getline(&string, &n, stdin);

		write(STDOUT_FILENO, string, line);

		free(string);
		
	}
	return (0);
}
