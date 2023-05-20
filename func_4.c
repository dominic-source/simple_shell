#include "main.h"

/**
 * str_num - convert string to integer
 * @str: string
 * Return: number
 */
int str_num(char *str)
{
	int num = 0, i = 0, sign = 1;

	if (str[i] == '-')
	{
		i = 1;
		sign = -1;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = (num * 10) + (str[i] - '0');
		else
			return (0);
	}
	return (num * sign);
}

/**
 * my_exit - exit from the function
 *
 *
 */
void my_exit(void)
{
	int status = 0;

	if (arc[1] != NULL)
		status = str_num(arc[1]);
	if (status >= 0)
	{
		free_mem(arc, lptr, NULL);
		free_mem(_environ, NULL, NULL);
		exit(status);
	}
	else if (status < 0)
		perror(argv[0]);
	child_pid = -1;
}

/**
 * print_env - prints environmental variables
 *
 */
void print_env(void)
{
	int i;

	for (i = 0;_environ[i] != NULL; i++)
	{
		write(out, _environ[i], _strlen(_environ[i]));
		write(out, "\n", 1);
	}
	child_pid = -1;
}
