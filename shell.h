#ifndef _SHELL_H_
#define _SHELL_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * struct er_val - Struct built
 *
 * @argv_0: firts command.
 * @e_c: prompt counter.
 * @exit_status: exit stats value.
 */
typedef struct er_val
{
	char *argv_0;
	int e_c;
	int exit_status;
} err_t;

/**
 * struct built - Struct built
 *
 * @bui: builtin name.
 * @f: The function associated
 */
typedef struct built
{
	char *bui;
	int (*f)(char **av, char *line, char ***env, err_t *errval);
} built_t;

extern char **environ;

/*generic functions*/
int _strlen(char *s);
int print_string(char *s);
char *_strdup(char *str);
void _freearrp(char **av);
void *_calloc(unsigned int nmemb, unsigned int size);
char *str_concat(char *s1, char *s2);
char *_strtok(char *s, char *delim);
char **_cpyarrp(char **arrp);
int findenv(char **env, char *cmp_val);
void print_err_numb(int n);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
void rev_string(char *s);

/*shell functions*/
char *read_line(char **env, err_t *errval);
char **split_line(char *line);
int (*builtins(char *av_0))(char **, char *, char ***, err_t *);
char **path_exp(char **av, char **env);
int exec_func(char **av, char *line, char **env, err_t *errval);

/*Builtins*/
int exit_f(char **av, char *line, char ***env, err_t *errval);
int env_f(char **av, char *line, char ***env, err_t *errval);
int setenv_f(char **av, char *line, char ***env, err_t *errval);
int unsetenv_f(char **av, char *line, char ***env, err_t *errval);
int change_dir(char **av, char *line, char ***env, err_t *errval);
int help_f(char **av, char *line, char ***env, err_t *errval);

/*error functions*/
void print_err(err_t *errval, int ca, char *av_1);
void printerr_help(err_t *errval, char **av, int i);

/*cd builtin function*/
char **setenv_cd(char *name_var, char *cont_var, char **env);

#endif
