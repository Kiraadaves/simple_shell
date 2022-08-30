#include "shell.h"

/**
 * main - main function that accepts input 
 * @argc: command line argument count
 * @agrv: command line vector count
 * Return:
 */

int main (int argc __attribut__((unused)), char **agrv)
{
	char *line;
	(void)argv; signal(SIGINT, ctrl_C);

	while (1)
	{
		write("#shell$ ", STDOUT_FILENO);
		line = _getline();
