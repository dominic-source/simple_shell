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

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if equal, -ve if s1 is less, +ve if s1 is greater
 */

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strncmp - compares the first n bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 *
 * Return: 0 if equal, -ve if s1 is less, +ve if s1 is greater
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i] && i < (n - 1))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * _strcat - appends src string to dest string
 * @dest: original string
 * @src: string to be appended
 *
 * Return: a pointer to the resulting dest string
 */

char *_strcat(char *dest, const char *restrict src)
{
	if (dest == NULL || src == NULL)
		return NULL;
	int i, j, m;

	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	j = 0;
	while (src[j] != '\0')
	{
		j++;
	}
	m = 0;
	while (src[m] != '\0')
	{
		dest[i] = src[m];
		i++;
		m++;
	}
	dest[i] = '\0';

	return (dest);
}
