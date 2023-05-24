#include "main.h"

#define HASH_ME\
	do {\
		for (i = 0; arc[i] != NULL; i++)\
		{\
			if (_strcmp(arc[i], "#") == 0)\
			{\
				free(arc[i]);\
				arc[i] = NULL;\
				j = i + 1;\
				for (; arc[j] != NULL; j++)\
				{\
					free(arc[j]);\
				} \
				free(arc[j]);\
				break;\
			} \
		} \
	} \
	while (0)
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
	status = 0;
	alias = NULL;
	commands_cnt = 0;
	_env();
	signal(SIGINT, hndl_sgnl);

	if (ac > 5 || av == NULL)
		return (-1);
	if (av[1] != NULL)
	{
		in = open(av[1], O_RDONLY);
		if (in == -1)
		{
			perror(av[1]);
			close(in);
		}
		interactive = 0;
	}
	while (interactive)
	{
		write(out, "($) ", 4);
		interact();
	}
	while (!interactive)
		interact();
	free_mem(_environ, NULL, NULL);
	free_mem(alias, NULL, NULL);
	alias = NULL;
	if (av[1] != NULL)
		close(in);
	return (0);
}

/**
 * interact - non interactive mode for the shell
 *
 */
void interact(void)
{
	char *hdl = NULL;
	size_t len = 0;
	ssize_t line = 0;
	int ex, chk = -1;

	if (line != -1)
		line = _getline(&lptr, &len, in);
	if (line == -1)
	{
		if (interactive)
			write(out, "\n", 1);
		free_mem(_environ, NULL, NULL);
		free_mem(alias, NULL, NULL);
		exit(0);
	}
	arc = NULL;
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
		free_mem(arc, lptr, hdl);
	}
}

/**
 * handle_cmd - concatenate /bin/ to commands if it is absent
 * Return: pointer to str
 */
char *handle_cmd(void)
{
	char *temp = "/bin/", *bin;
	int length, handle;

	if (arc == NULL)
		return (NULL);
	handle = handle_func_cmd();
	if ((arc[0] == NULL || _strlen(arc[0]) <= 0) && handle == 0)
	{
		free_mem(arc, NULL, NULL);
		return (NULL);
	}
	else if (_strncmp(temp, arc[0], 5) != 0 && handle == 0)
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
	else if (_strncmp(temp, arc[0], 5) == 0 && handle == 0)
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
	char *lptrcpy = NULL, *str, *delim = " ";
	int count = 1, i, j;

	if (*lptr == '\0' || lptr == NULL)
	{
		arc = NULL;
		return (NULL);
	}
	lptrcpy = malloc(sizeof(char) * (_strlen(lptr) + 1));
	if (lptrcpy == NULL)
		return (NULL);
	_strcpy(lptrcpy, lptr);
	_strtok(lptrcpy, delim);
	while (_strtok(NULL, delim) != NULL)
		count++;
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
		_strcpy(arc[i], str);
		str = _strtok(NULL, delim);
	}
	arc[i] = NULL;
	free_mem(NULL, lptrcpy, NULL);
	HASH_ME;
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
		free_mem(alias, NULL, NULL);
		alias = NULL;
		exit(EXIT_SUCCESS);
	}
}
