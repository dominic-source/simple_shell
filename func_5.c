#include "main.h"

/**
 * _cd - changes the working directory
 *
 * Return: 0 on success and -1 if not successful
 */

int _cd(void)
{
	char *hmdir, *wd, *tempwd;
	static char *previous_wd;
	static int check;
	int i;

	hmdir = _getenv("HOME");
	if (arc[1] == NULL)
	{
		previous_wd = getcwd(NULL, 0);
		i = chdir(hmdir);
	}
	else
	{
		wd = malloc(sizeof(char) * (_strlen(getcwd(NULL, 0)) + _strlen(arc[1]) + 2));
		_strcpy(wd, getcwd(NULL, 0));
		wd = _strcat(wd, "/");
		wd = _strcat(wd, arc[1]);
		if ((_strcmp(arc[1], "-")) == 0 && (check != -1))
		{
			previous_wd = getcwd(NULL, 0);
			i = chdir("/");
		}
		else if ((_strcmp(arc[1], "-")) == 0 && (check == -1))
		{
			tempwd = getcwd(NULL, 0);
			i = chdir(previous_wd);
			previous_wd = tempwd;
		}
		else
		{
			previous_wd = getcwd(NULL, 0);
			i = chdir(wd);
		}
		free(wd);
	}
	if (i == -1)
		return (-1);
	_setenv("PWD", getcwd(NULL, 0), 1);
	check = -1;
	return (0);
}
