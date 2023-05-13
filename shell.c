#include "main.h"

/**
 * main - start a simple shell
 * @ac: count of argument
 * @av: arguments
 * Return: -1 or 0
 */
int main (int ac, char *av[])
{
	char *arc[2];
	size_t len = 0;
	ssize_t line;
	int status, interactive, ex;

	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	er = STDERR_FILENO;
	interactive = isatty(in);
	if (ac >= 3 || av == NULL)
		return (-1);
	while (interactive)
	{
		write(out,"($) ", 4);
		line = getline(&lptr, &len, stdin);
		if (line == -1)
		{
			write(out, "\n", 1);
			free(lptr);
			exit(0);
		}
		child_pid = fork();
		if (child_pid == 0)
		{
			rm_nwl(lptr);
			arc[0] = lptr;
			arc[1] = NULL;
			ex = execve(lptr, arc, NULL);
			if (ex == -1)
				perror(av[0]);
			exit(1);
		}
		else
		{
			wait(&status);
		}
	}

	while(!interactive)
	{
		line = getline(&lptr, &len, stdin);
		if (line == -1)
		{
			free(lptr);
			exit(0);
		}
		rm_nwl(lptr);
		child_pid = fork();
		if (child_pid == 0)
		{
			arc[0] = lptr;
			arc[1] = NULL;
			ex = execve(lptr, arc, NULL);
			if (ex == -1)
				perror(av[0]);
			exit(1);
	      	}
		else
		{
			wait(&status);
		}
	}
	free(lptr);
	return (0);
}
