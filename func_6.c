#include "main.h"

/**
 * handle_func_cmd - handles commands function
 *
 * Return: -1 or 0
 */
int handle_func_cmd(void)
{
	int value = -1;

	_echo_expand();
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
		if (_unsetenv(arc[1]) == -1)
			print_error("cannot unsetenv");
		child_pid = -1;
		return (-1);
	}
	else if (cd_d_alias() == -1)
		return (-1);
	return (0);
}
/**
 * cd_d_alias - continuation of the handle_func_cmd
 * Return: -1 or 0
 */
int cd_d_alias(void)
{
	char *a = arc[1];
	int i, print_alias = 1, value = -1;

	if (_strcmp(arc[0], "cd") == 0)
	{
		child_pid = -1;
		value = _cd();
		if (value == -1)
			print_error("cannot change directory");
		return (-1);
	}
	else if (_strcmp(arc[0], "alias") == 0)
	{
		child_pid = -1;
		if (arc[1] != NULL)
		{
			for (i = 0; a[i] != '\0'; i++)
			{
				if (a[i] == '=')
				{
					print_alias = 0;
					break;
				}
			}
			if (print_alias == 0)
				if (set_alias() == 0)
					error_alias("Error", arc[1]);
			print_alias_func(print_alias);
		}
		else if (alias != NULL)
			for (i = 0; alias[i] != NULL; i++)
			{
				write(out, alias[i], _strlen(alias[i]));
				write(out, "\n", 1);
			}
		return (-1);
	}
	return (0);
}

/**
 * print_alias_func - prints alias
 * @print_alias: 1 or 0
 */
void print_alias_func(int print_alias)
{
	int i, j, length, c = -1;

	for (i = 1; arc[i] != NULL && print_alias; i++)
	{
		if (alias != NULL)
		{
			for (j = 0; alias[j] != NULL; j++)
			{
				c = _strncmp(alias[j], arc[i], _strlen(arc[i]));
				if (c == 0)
				{
					length = _strlen(alias[j]);
					write(out, alias[j], length);
					write(out, "\n", 1);
					break;
				}
			}
			if (c != 0)
				error_alias("not found", arc[i]);
		}
		else
		{
			error_alias("not found", arc[i]);
			break;
		}
	}
}

/**
 * set_alias - create or set alias
 * Return: 0 or 1
 */
int set_alias(void)
{
	char **temp = NULL;
	int i, j, a_count = 0;

	for (i = 1; arc[i] != NULL; i++)
	{
		if (alias == NULL)
		{
			alias = malloc(sizeof(char *) * 2);
			if (alias == NULL)
				return (0);
			alias[0] = malloc(sizeof(char) * (_strlen(arc[i]) + 1));
			if (alias[0] == NULL)
				return (0);
			_strcpy(alias[0], arc[i]);
			alias[1] = NULL;
		}
		else if (alias != NULL)
		{
			for (j = 0; alias[j] != NULL; j++)
				a_count++;
			temp = malloc(sizeof(char *) * (a_count + 2));
			if (temp == NULL)
				return (0);
			for (j = 0; alias[j] != NULL; j++)
			{
				temp[j] = alias[j];
			}

			temp[j] = malloc(sizeof(char) * (_strlen(arc[i]) + 1));
			if (temp[j] == NULL)
				return (0);
			_strcpy(temp[j], arc[i]);
			temp[j + 1] = NULL;
			alias = temp;
			free(temp[j]);
		}
	}
	return (1);
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
	int i;

	for (i = 0; arc[i] != NULL; i++)
	{
		if (_strcmp(arc[i], "$?") == 0)
		{
			num_str(exit_status, str_n);
			free(arc[i]);
			arc[1] = malloc(sizeof(char) * (_strlen(str_n) + 1));
			if (arc[i] == NULL)
				return;
			_strcpy(arc[i], str_n);
		}
		else if (_strcmp(arc[i], "$$") == 0)
		{
			num_str(getpid(), str_n);
			free(arc[i]);
			arc[i] = malloc(sizeof(char) * (_strlen(str_n) + 1));
			if (arc[i] == NULL)
				return;
			_strcpy(arc[i], str_n);
		}
		else if (_strncmp(arc[i], "$", 1) == 0)
		{
			if (arc[i][1] == '\0')
				str = "$";
			else
				str = _getenv(&(arc[i][1]));
			free(arc[i]);
			arc[i] = malloc(sizeof(char) * (_strlen(str) + 1));
			if (arc[i] == NULL)
				return;
			_strcpy(arc[i], str);
		}
	}
}
