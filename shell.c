#include "main.h"

/**
 * main - start a simple shell
 * @ac: count of argument
 * @av: arguments
 * Return: -1 or 0
 */
int main(int ac, char *av[])
{
	/* Global variables */
	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	er = STDERR_FILENO;
	interactive = isatty(in);
	argv = av;
	commands_cnt = 0;
	_env();
	signal(SIGINT, hndl_sgnl);

	if (ac >= 3 || av == NULL)
		return (-1);
	while (interactive)
	{
		write(out, "($) ", 4);
		interact(interactive);
	}
	while (!interactive)
		interact(interactive);
	free_mem(_environ, NULL, NULL);
	return (0);
}

/**
 * interact - non interactive mode for the shell
 * @mode: interactive mode or not
 */
void interact(int mode)
{
	char *hdl = NULL;
	size_t len = 0;
	ssize_t line;
	int status, ex, chk = -1;

	line = _getline(&lptr, &len, in);
	if (line == -1)
	{
		write(out, "\n", 1);
		free_mem(_environ, NULL, NULL);
		exit(0);
	}
	commands_cnt++;
	rm_nwl(lptr);
	child_pid = 1;
	arc = alloc_mem();
	hdl = handle_cmd();
	if (hdl != NULL)
		chk = access(hdl, F_OK | X_OK);
	if ((arc == NULL || chk != 0) && child_pid != -1)
		print_error("not found");
	else if (chk == 0 && child_pid != -1)
		child_pid = fork();

	if (child_pid == 0)
	{
		ex = execve(hdl, arc, _environ);
		if (ex == -1)
			perror(argv[0]);
		free_mem(arc, lptr, hdl);
		exit(0);
	}
	else
	{
		wait(&status);
		if (mode)
			free_mem(arc, NULL, NULL);
		free_mem(NULL, lptr, hdl);
	}
}

/**
 * handle_cmd - concatenate /bin/ to commands if it is absent
 * Return: pointer to str
 */
char *handle_cmd(void)
{
	char *temp = "/bin/";
	char *bin;
	int length;

	if (arc[0] == NULL || _strlen(arc[0]) <= 0)
	{
		free_mem(arc, NULL, NULL);
		return (NULL);
	}
	else if (_strcmp(arc[0], "exit") == 0)
		my_exit();
	else if (_strcmp(arc[0], "env") == 0)
		print_env();
	else if (_strncmp(temp, arc[0], 5) != 0)
	{
		length = _strlen(arc[0]) + 6;
		bin = malloc(sizeof(char) * length);
		if (bin == NULL)
		{
			free_mem(arc, lptr, NULL);
			return (NULL);
		}
		_strcpy(bin, temp);
		_strcat(bin, arc[0]);
		return (bin);
	}
	else if (_strncmp(temp, arc[0], 5) == 0)
	{
		length = _strlen(arc[0]) + 1;
		bin = malloc(sizeof(char) * length);
		if (bin == NULL)
		{
			free_mem(arc, lptr, NULL);
			return (NULL);
		}
		_strcpy(bin, arc[0]);
		return (bin);
	}
	return (NULL);
}

/**
 * alloc_mem - allocate memory for the commands and arguments
 *
 * Return: pointers to strings (commands)
 */
char **alloc_mem(void)
{
	char *lptrcpy = NULL;
	char *str;
	char *delim = " ";
	int count = 1, i;

	lptrcpy = malloc(sizeof(char) * (_strlen(lptr) + 1));
	if (lptrcpy == NULL)
		return (NULL);
	_strcpy(lptrcpy, lptr);
/* count the number of arguments */
	_strtok(lptrcpy, delim);
	while (_strtok(NULL, delim) != NULL)
		count++;
	/* allocate memory for what was counted */
	arc = malloc(sizeof(char *) * (count + 1));
	if (arc == NULL)
	{
		free(lptrcpy);
		return (NULL);
	}
	str = _strtok(lptr, delim);
	for (i = 0; str != NULL; i++)
	{
		arc[i] = malloc(sizeof(char) * (_strlen(str) + 1));
		if (arc[i] == NULL)
		{
			i--;
			for (; i >= 0; i--)
				free(arc[i]);
			free_mem(arc, lptrcpy, NULL);
			return (NULL);
		}
		/* initialize the allocated memory */
		_strcpy(arc[i], str);

		str = _strtok(NULL, delim);
	}
	arc[i] = NULL;
	free_mem(NULL, lptrcpy, NULL);
	return (arc);
}

/**
 * hndl_sgnl - handle signal
 * @sig: signal
 */
void hndl_sgnl(int sig)
{
	if (sig == SIGINT)
	{
		write(out, "\n", 1);
		free_mem(_environ, NULL, NULL);
		exit(EXIT_SUCCESS);
	}
}
