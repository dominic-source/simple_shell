#include "main.h"

/**
 * _env - initializes shell environment variable
 *
 * Return: nothing
 */

void _env(void)
{
	int i, j, len = 0;

	while (environ[len] != NULL)
	{
		len++;
	}
	_environ = (char **)malloc((len + 1) * sizeof(char *));
	if (_environ == NULL)
		return;
	for (i = 0; environ[i] != NULL; i++)
	{
		len = 0;
		while (environ[i][len] != '\0')
		{
			len++;
		}
		_environ[i] = (char *)malloc((len + 1) * sizeof(char));
		for (j = 0; environ[i][j] != '\0'; j++)
		{
			_environ[i][j] = environ[i][j];
		}
		_environ[i][j] = '\0';
	}
	_environ[i] = NULL;
}

/**
 * _setenv - adds the variable name with value to the shell environment
 * @name: name to be added or updated
 * @value: value of name to be added
 * @overwrite: indicator whether to overwite existing name or not
 *
 * Return: 0 if successful and -1 if not successful
 */

int _setenv(const char *name, const char *value, int overwrite)
{
	int i, j, index = -1;
	char *nm, *buffer, *envcpy, **new_environ;

	for (i = 0; _environ[i] != NULL; i++)
	{
		buffer = (char *)malloc(_strlen(_environ[i]) * sizeof(char));
		if (buffer == NULL)
			return (-1);
		envcpy = _strcpy(buffer, _environ[i]);
		nm = _strtok(envcpy, "=");
		j = _strcmp(nm, name);
		free(buffer);
		if (j == 0 && overwrite == 0)
			return (0);
		else if (j == 0 && overwrite != 0)
		{
			index = i;
			break;
		}
	}
	nm = (char *)malloc(_strlen(name) + _strlen(value) + 2);
	if (nm == NULL)
		return (-1);
	_strcpy(nm, name);
	_strcat(nm, "=");
	_strcat(nm, value);
	if (index != -1)
	{
		free(_environ[index]);
		_environ[index] = nm;
	}
	else
	{
		new_environ = (char **)realloc(_environ, (sizeof(char *) * (i + 2)));
		if (new_environ == NULL)
		{
			free(nm);
			return (-1);
		}
		_environ = new_environ;
		_environ[i] = nm;
		_environ[i + 1] = NULL;
	}
	return (0);
}
