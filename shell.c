#include "main.h"
void free_mem(char **args, char *a, char *b);
char **alloc_mem(void);
void hndl_sgnl(int sig);
char *handle_cmd(void);
void interact(int mode);
char **arc = NULL;
void _env(void);

/**
 * main - start a simple shell
 * @ac: count of argument
 * @av: arguments
 * Return: -1 or 0
 */
int main(int ac, char *av[])
{
	int interactive;

	/* Global variables */
	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	er = STDERR_FILENO;
	interactive = isatty(in);
	argv = av;
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
	char *hdl;
	size_t len = 0;
	ssize_t line;
	int status, ex, chk;

	line = _getline(&lptr, &len, in);
	if (line == -1)
	{
		write(out, "\n", 1);
		free_mem(_environ, NULL, NULL);
		exit(0);
	}
	rm_nwl(lptr);
	arc = alloc_mem();
	hdl = handle_cmd();
	chk = access(arc[0], F_OK | X_OK);
	if (arc == NULL || hdl == NULL || chk != 0)
	{
		child_pid = 1;
		perror(argv[0]);
	}
	else if (chk == 0)
		child_pid = fork();

	if (child_pid == 0)
	{
		ex = execve(arc[0], arc, _environ);
		if (ex == -1)
			perror(argv[0]);
		free_mem(arc, lptr, NULL);
		exit(0);
	}
	else
	{
		wait(&status);
		if (mode)
			free_mem(arc, NULL, NULL);
		free_mem(NULL, lptr, NULL);
	}
}

/**
 * handle_cmd - concatenate /bin/ to commands if it is absent
 * Return: pointer to str
 */
char *handle_cmd(void)
{
	char *bin = "/bin/";
	char temp[50];
	int length;

	if (arc[0] == NULL || _strlen(arc[0]) <= 0)
	{
		free_mem(arc, NULL, NULL);
		return (NULL);
	}
	if (_strncmp(bin, arc[0], 5) != 0)
	{
		_strcpy(temp, arc[0]);
		length = _strlen(arc[0]) + 6;
		free(arc[0]);
		arc[0] = malloc(sizeof(char) * length);
		if (arc[0] == NULL)
		{
			free_mem(arc, lptr, NULL);
			return (NULL);
		}
		_strcpy(arc[0], bin);
		_strcat(arc[0], temp);
	}
	return (arc[0]);
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
