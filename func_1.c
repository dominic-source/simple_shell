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

char *_strcat(char *dest, const char *src)
{
	int i, j, m;

	if (dest == NULL || src == NULL)
		return (NULL);
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

/**
 * _strtok - breaks a string into non empty tokens
 * @str: input string
 * @delim: the delimiter
 *
 * Return: A pointer to the next token or NULL in none
 */

char *_strtok(char *str, const char *delim)
{
	static char *nxtoken;
	char *crtoken;
	int i = 0;

	if (delim == NULL)
		return (NULL);
	if (str != NULL)
	{
		while (str[i] == *delim)
		{
			i++;
		}
		if (str[i] == '\0')
			return (NULL);
		crtoken = &str[i];
	}
	else if (str == NULL)
	{
		if (nxtoken == NULL || nxtoken[0] == '\0')
			return (NULL);
		str = nxtoken;
		crtoken = str;
	}
	while (str[i] != *delim && str[i] != '\0')
	{
		i++;
	}
	if (str[i] == '\0')
	{
		nxtoken = NULL;
		return (crtoken);
	}
	str[i] = '\0';
	i++;
	while (str[i] == *delim)
	{
		i++;
	}
	nxtoken = &str[i];
	return (crtoken);
}

