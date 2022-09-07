#include "shell.h"

/**
 * shell_loop - reads a user innput and checks if the
 * shell should be ran interactively or not.
 * it removes comments and tokenizes, then
 * executes the tokenized command while running
 * infinitely.
 * @var: shell global variable
 */

void shell_loop(shell_t *var)
{
	char *line, *op, **args, **logic_cmd;
	int i;

	signal(SIGINT, ctrl_C_func);
	while (1)
	{
		i = 0;
		non_interactive(var);
		_printf(" #shell$ ", STDOUT_FILENO);
		line = shell_readline();
		if (!_strlen(line))
		{
			free(line);
			if (isatty(STDIN_FILENO))
				continue;
		}
		if (!line)
		{
			if (isatty(STDIN_FILENO))
				break;
		}
		remove_comment(line);
		args = tokenize(line, ";");
		while (args[i])
		{
			logic_cmd = logic_token(args[i++]);
			op = logic_cmd[1];
			while (logic_cmd[0])
			{
				execute_logic(logic_cmd[0], var);
				var->cmd_counter += 1;
				if (!logic_cmd[2])
					break;
				if (_strcmp(op, AND_DELIM) == 0)
				{
					if (var->err_status == 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
				else if (_strcmp(op, OR_DELIM) == 0)
				{
					if (var->err_status != 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
			}
		}
		free_tokenized(args);
	}
	free(line);
}

/**
 * non_interactive - runs shell in non interactive mode
 * @p: shell global variable
 */

void non_interactive(shell_t *p)
{
	char **args, **logic_cmd;
	char *line, *op;
	int i = 0;

	if (isatty(STDIN_FILENO) == 0)
	{
		line = shell_readline();
		remove_comment(line);
		args = tokenize(line, ";");
		while (args[i])
		{
			logic_cmd = logic_token(args[i++]);
			op = logic_cmd[1];
			while (logic_cmd[0])
			{
				execute_logic(logic_cmd[0], p);
				p->cmd_counter += 1;
				if (!logic_cmd[2])
					break;
				if (_strcmp(op, AND_DELIM) == 0)
				{
					if (p->err_status == 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
				else if (_strcmp(op, OR_DELIM) == 0)
				{
					if (p->err_status != 0)
						logic_cmd = logic_token(logic_cmd[2]);
					else
						break;
				}
			}
		}
		free_tokenized(args);
		free_tokenized(environ);
		free(line);
	}
}

/**
 * check_cmd_type - checks the type of command
 * @command: command to be checked
 * Return: constant variable that reprsents the command
 */

int check_cmd_type(char *command)
{
	static char *internal_cmd[] = {
		"exit", "cd", "help", "env", "setenv",
		"unsetenv", "alias", NULL
	};
	char *path = NULL;
	int i = 0;

	while (command[i])
	{
		if (command[i++] == '/')
			return (TERM_CMD);
	}
	for (i = 0; internal_cmd[i]; i++)
	{
		if (_strcmp(command, internal_cmd[i]) == 0)
			return (INTERNAL_CMD);
	}
	path = check_path(command);
	if (path)
	{
		free(path);
		return (PATH_CMD);
	}
	return (INVALID_CMD);
}

/**
 * shell_execute - launches the command to be executed
 * @command: command to be launched
 * @cmd_type: type of command
 * @var: struct for shell name and old path
 * Return: 1
 */
void shell_execute(char **command, int cmd_type, shell_t *var)
{
	pid_t PID, W_PID __attribute__((unused));
	int state;

	if (cmd_type == PATH_CMD || cmd_type == TERM_CMD)
	{
		PID = fork();
		if (PID == 0)
		{
			shell_launch(command, cmd_type, var);
		}
		else if (PID < 0)
		{
			perror("Error Creating fork");
			return;
		}
		else
		{
			do {
				W_PID = waitpid(PID, &state, WUNTRACED);
			} while (!WIFEXITED(state) && !WIFSIGNALED(state));
		}
	}
	else
		shell_launch(command, cmd_type, var);
	var->err_status = state / 256;
}
/**
 * _strcpy - copies contents of a string to another string
 * @dest: destination string
 * @src: string being copied
 * Return: returns a pointer to the new string
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i]; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}
