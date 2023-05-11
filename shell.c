#include "main.h"

/**
 * main - start a simple shell
 * @ac: count of argument
 * @av: arguments
 * Return: -1 or 0
 */
int main (int ac, char *av[])
{
	size_t len = 0;
	ssize_t line;
	int status;

	if (ac >= 3 || av == NULL)
		return (-1);
	while (1)
	{
		write(out,"($) ", 4);
		line = getline(&lptr, &len, stdin);
		while (line != -1)
		{
			child_pid = fork();
			if (child_pid == 0)
			{

				execve(lptr, &lptr, NULL);
			}
			else
			{
				wait(&status);
				free(lptr);
			}
			line = getline(&lptr, &len, stdin);
		}
		free(lptr);
	}
	return (0);
}
