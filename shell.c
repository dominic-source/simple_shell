#include "main.h"
#define S_CD (_strncmp(temp, arc[0], 5) == 0 || _strncmp(".", arc[0], 1) == 0)
#define M_CD (_strncmp(temp, arc[0], 5) != 0 && _strncmp(".", arc[0], 1) != 0)
#define WAIT_FREE\
	do {\
		wait(&stl);\
		((child_pid == -1 || child_pid == 1) ?\
		 (exit_status = status) : (exit_status = WEXITSTATUS(stl)));\
		free_mem(arc, lptr, hdl);\
	} \
	while (0)

#define HASH_ME\
	do {\
		arc[i] = NULL;\
		free_mem(NULL, lptrcpy, NULL);\
		for (i = 0; arc[i] != NULL; i++)\
		{\
			if (_strncmp(arc[i], "#", 1) == 0)\
			{\
				free_mem(NULL, arc[i], NULL);\
				arc[i] = NULL;\
				j = i + 1;\
				for (; arc[j] != NULL; j++)\
				{\
					free_mem(NULL, arc[j], NULL);\
				} \
				free_mem(NULL, arc[j], NULL);\
				break;\
			} \
		} \
	} \
	while (0)
#define FI_WRITE\
	do {\
		cmd = num_str(commands_cnt, str);\
		write(er, argv[0], _strlen(argv[0]));\
		write(er, ": ", 2);\
		write(er, cmd, _strlen(cmd));\
		write(er, ": Can't open ", 13);\
		write(er, argv[1], _strlen(argv[1]));\
		write(er, "\n", 1);\
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
	char str[10], *cmd;
	/* Global variables */
	in = STDIN_FILENO;
	out = STDOUT_FILENO;
	er = STDERR_FILENO;
	interactive = isatty(in);
	argv = av;
	previous_wd = NULL;
	alias = NULL;
	exit_status = 0;
	status = 0;
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
			FI_WRITE;
			exit_status = 127;
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
	free_mem(_environ, previous_wd, NULL);
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
	int ex, chk = -1, stl;

	if (line != -1)
		line = _getline(&lptr, &len, in);
	if (line == -1)
	{
		if (interactive)
			write(out, "\n", 1);
		free_mem(_environ, NULL, NULL);
		free_mem(alias, previous_wd, NULL);
		exit(exit_status);
	}
	arc = NULL;
	commands_cnt++;
	rm_nwl(lptr);
	cdc = 1;
	child_pid = 1;
	arc = alloc_mem();
	hdl = handle_cmd();
	if (hdl != NULL)
		chk = access(hdl, R_OK | F_OK | X_OK);
	if ((arc == NULL || chk != 0) && child_pid != -1)
		print_error("not found");
	else if (chk == 0 && child_pid != -1)
		child_pid = fork();
	if (child_pid == 0)
	{
		ex = execve(hdl, arc, _environ);
		if (ex == -1)
			print_error(NULL);
		free_mem(arc, lptr, hdl);
		exit(126);
	}
	else
		WAIT_FREE;
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
	else if ((M_CD) && handle == 0 && access(arc[0], F_OK | X_OK) != 0)
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
	else if (((S_CD) && handle == 0) || access(arc[0], F_OK | X_OK) == 0)
	{
		bin = malloc(sizeof(char) * (_strlen(arc[0]) + 1));
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
	char *lptrcpy = NULL, *str = NULL, *delim = " ", *tmp;
	int count = 1, i, j;

	if (*lptr == '\0' || lptr == NULL)
		return (NULL);
	lptrcpy = malloc(sizeof(char) * (_strlen(lptr) + 1));
	if (lptrcpy == NULL)
		return (NULL);
	_strcpy(lptrcpy, lptr);
	tmp = _strtok(lptrcpy, delim);
	if (tmp == NULL || _strncmp(tmp, "#", 1) == 0)
	{
		free(lptrcpy);
		return (NULL);
	}
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
		free_mem(_environ, previous_wd, NULL);
		free_mem(alias, NULL, NULL);
		alias = NULL;
		exit(exit_status);
	}
}
