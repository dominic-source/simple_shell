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
	if (_strcmp(arc[0],"env") == 0)
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
