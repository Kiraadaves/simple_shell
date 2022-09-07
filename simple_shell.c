#include "shell.h"

#define RED   "\x1B[31m"
#define BLU   "\x1B[34m"
#define BOLD  "\x1b[1m"
#define RESET "\x1B[0m"

/**
 * handle_sign - ignore the ctrl+2 and re-start the shell process.
 * @sig: number of signal.
 * Return: Always success.
 */
void handle_sign(int sig)
{
	char *prompt;
	(void) sig;

	prompt = BLU BOLD "#Shell" RESET RED BOLD "$ " RESET;
	signal(SIGINT, handle_sign);
	write(STDIN_FILENO, "\n", 1);
	write(STDIN_FILENO, prompt, _strlen(prompt));
}

/**
 * main - simple shell.
 * @argc: arguments counter.
 * @argv: arguments vector.
 * @env: enviromental variables vector.
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	char **av;
	char **env_cp;
	int status = 1;
	int chk_build = 0;
	err_t errval;
	(void)argc;

	errval.argv_0 = argv[0];
	errval.e_c = 0;
	errval.exit_status = 0;
	env_cp = _cpyarrp(env);
	signal(SIGINT, handle_sign);

	while (status)
	{
		line = read_line(env_cp, &errval);
		errval.e_c = errval.e_c + 1;
		av = split_line(line);
		if (av == NULL)
		{
			free(line);
			continue;
		}
		chk_build = (*builtins(av[0]))(av, line, &env_cp, &errval);
		if (chk_build == 1)
		{
			chk_build = 0;
			free(line);
			_freearrp(av);
			continue;
		}
		av = path_exp(av, env_cp);
		status = exec_func(av, line, env_cp, &errval);

		free(line);
		_freearrp(av);
	}
	return (0);
}
