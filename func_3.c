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
