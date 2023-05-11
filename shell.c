#include "main.h"

/**
 * main - start a simple shell
 * @ac: count of argument
 * @av: arguments
 * Return: -1 or 0
 */
int main (int ac, char *av[])
{
	size_t *len = 0;
	ssize_t line;

	if (ac >= 3)
		return (-1);
	while (1)
	{
		write(out,"($) ", 4);
		line = getline(lptr, len, stdin);
		while (line != -1)
		{
			child_pid = fork();
			if (child_pid == 0)
			{

				execve(lptr, av, NULL);
			}
			else
			{
				wait(0);
				free(lptr);
			}
			line = getline(lptr, len, stdin);
		}
	}
	return (0);
}
