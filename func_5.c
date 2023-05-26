#include "main.h"

#define MCD_DASH\
	do {\
		free_mem(NULL, previous_wd, NULL);\
		previous_wd = getcwd(NULL, 0);\
		i = chdir("/");\
	} \
	while (0)

#define MCD_DASH2\
	do {\
		tempwd = getcwd(NULL, 0);\
		i = chdir(previous_wd);\
		free_mem(NULL, previous_wd, NULL);\
		previous_wd = tempwd;\
	} \
	while (0)

#define MCD_DASH3\
	do {\
		free_mem(NULL, previous_wd, NULL);\
		previous_wd = getcwd(NULL, 0);\
		i = chdir(wd);\
	} \
	while (0)
/**
 * _cd - changes the working directory
 *
 * Return: 0 on success and -1 if not successful
 */
int _cd(void)
{
	char *hmdir, *wd, *tempwd, *f = NULL, *s = NULL, *j = NULL;
	static int check;
	int i;

	hmdir = _getenv("HOME");
	if (arc[1] == NULL)
	{
		free_mem(NULL, previous_wd, NULL);
		previous_wd = getcwd(NULL, 0);
		i = chdir(hmdir);
	}
	else
	{
		j = getcwd(NULL, 0);
		wd = malloc(sizeof(char) * (_strlen(j) + _strlen(arc[1]) + 2));
		f = getcwd(NULL, 0);
		_strcpy(wd, f);
		wd = _strcat(wd, "/");
		wd = _strcat(wd, arc[1]);
		if ((_strcmp(arc[1], "-")) == 0 && (check != -1))
			MCD_DASH;
		else if ((_strcmp(arc[1], "-")) == 0 && (check == -1))
			MCD_DASH2;
		else
			MCD_DASH3;
		free(wd);
	}
	if (i == -1)
	{
		free_mem(NULL, f, j);
		return (-1);
	}
	s = getcwd(NULL, 0);
	_setenv("PWD", s, 1);
	check = -1;
	free_mem(NULL, f, s);
	free_mem(NULL, j, NULL);
	status = 0;
	return (0);
}
