#include "main.h"

/**
 * rm_nwl - removes new line character in a string
 * @str: input string
 *
 * Return: string without newline character
 */

char *rm_nwl(char *str)
{
	int i;

	if (str == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
		}
	}
	return (str);
}
