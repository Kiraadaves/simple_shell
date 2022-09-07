#include "shell.h"

/**
 * _putcharerr - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putcharerr(char c)
{
	return (write(STDERR_FILENO, &c, 1));
}

/**
 * print_err_numb - print an int number to the standard output.
 * @n: number tested
 * Return: Always 0.
 */
void print_err_numb(int n)
{
	int dig = 0, tend = 1, iter = 1;
	unsigned int abs = n, numch, num;

	if (n < 0)
	{
		_putcharerr('-');
		abs = -n;
	}
	else
	{
		abs = n;
	}
	num = abs;

	while (num > 0)
	{
		num /= 10;
		dig++;
	}
	while (iter < dig)
	{
		tend *= 10;
		iter++;
	}
	while (tend >= 1)
	{
		numch = (abs / tend) % 10;
		_putcharerr(numch + '0');
		tend /= 10;
	}
}
