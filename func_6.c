#include "main.h"

/**
 * handle_func_cmd - handles commands function
 *
 * Return: -1 or 0
 */
int handle_func_cmd(void)
{
	int value = -1;

	if (arc[0] == NULL || *(arc[0]) == '\0')
		return (0);
	if (_strcmp(arc[0], "env") == 0)
	{
		print_env();
		child_pid = -1;
		return (-1);
	}
	else if (_strcmp(arc[0], "exit") == 0)
	{
		my_exit();
		child_pid = -1;
		return (-1);
	}
	else if (_strcmp(arc[0], "setenv") == 0)
	{
		if (arc[1] != NULL && arc[2] != NULL)
			value = _setenv(arc[1], arc[2], 1);
		child_pid = -1;
		if (value == -1)
			print_error("cannot setenv");
		return (-1);
	}
	else if (_strcmp(arc[0], "unsetenv") == 0)
	{
		value = _unsetenv(arc[1]);
		child_pid = -1;
		if (value == -1)
			print_error("cannot unsetenv");
		return (-1);
	}
	else if (_strcmp(arc[0], "echo") == 0)
	{
		_echo_expand();
		return (0);
	}
	else if (_strcmp(arc[0], "cd") == 0)
	{
		value = _cd();
		child_pid = -1;
		if (value == -1)
			print_error("cannot change directory");
		return (-1);
	}

	return (0);
}

/**
 * _echo_expand - expands echo argument
 *
 *
 */
void _echo_expand(void)
{
	char *str;
	char str_n[10];

	if (arc[1] != NULL)
	{
		if (_strcmp(arc[1], "$?") == 0)
		{
			num_str(status, str_n);
			printf("find: %i\n", status);
			free(arc[1]);
			arc[1] = malloc(sizeof(char) * (_strlen(str_n) + 1));
			if (arc[1] == NULL)
				return;
			_strcpy(arc[1], str_n);
		}
		else if (_strcmp(arc[1], "$$") == 0)
		{
			num_str(getpid(), str_n);
			free(arc[1]);
			arc[1] = malloc(sizeof(char) * (_strlen(str_n) + 1));
			if (arc[1] == NULL)
				return;
			_strcpy(arc[1], str_n);
		}
		else if (_strncmp(arc[1], "$", 1) == 0)
		{
			str = _getenv(&(arc[1][1]));
			free(arc[1]);
			arc[1] = malloc(sizeof(char) * (_strlen(str) + 1));
			if (arc[1] == NULL)
				return;
			_strcpy(arc[1], str);
		}
	}
}
