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
	char *nm, **new_environ;

	for (i = 0; _environ[i] != NULL; i++)
	{
		j = _strncmp(name, _environ[i], _strlen(name));
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
		new_environ = _realloc_env(i + 2);
		if (new_environ == NULL)
		{
			free(nm);
			return (-1);
		}
		_environ[i] = nm;
		_environ[i + 1] = NULL;
	}
	return (0);
}

/**
 * _unsetenv - deletes the vairble name from the environment
 * @name: name of environment to delete
 *
 * Return: returns zero on success, or -1 on error
 */

int _unsetenv(const char *name)
{
	int i, j, index = -1;

	for (i = 0; _environ[i] != NULL; i++)
	{
		j = _strncmp(name, _environ[i], _strlen(name));
		if (j != 0 &&( _environ[i + 1] == NULL) && (index == -1))
			return (0);
		else if (j == 0)
		{
			index = i;
		}
	}
	while (index < (i - 1))
	{
		_environ[index] = _environ[index + 1];
		index++;
	}
	_environ[index] = NULL;
	free(_environ[index + 1]);

	return (0);
}


/**
 * _realloc_env - reallocates memory to ptr to size n
 * @i: new memory size
 *
 * Return: pointer to the newly allocated memory
 */

char **_realloc_env(int i)
{
	int n;
	char **new_environ;

	new_environ = (char **)malloc(sizeof(char *) * (i));
	if (new_environ == NULL)
		return (NULL);
	for (n = 0; _environ[n] != NULL; n++)
	{
		new_environ[n] = _environ[n];
	}
	new_environ[n] = NULL;
	free(_environ);
	_environ = new_environ;
	for (n = 0; new_environ[n] != NULL; n++)
	{
		_environ[n] = new_environ[n];
	}

	return (_environ);
}

int main()
{
	int i = 0;
	char *str;

	_env();
	_setenv("PATH", "Lekki_Epe", 1);
	_setenv("STATE", "Abia", 1);
	while (_environ[i] != NULL)
	{
		str = _environ[i];
		printf("%s\n", str);
		i++;
	}
	_unsetenv("STATE");
	_unsetenv("LS_COLORS");
	_unsetenv("SHLVL");
	_unsetenv("PATH");
	_unsetenv("HOSTNAME");
	i = 0;
	while (_environ[i] != NULL)
	{
		str = _environ[i];
		printf("%s\n", str);
		i++;
	}

	return (0);
}
