#include "main.h"

/**
 * _strlen - count the length of string
 * @str - string to count
 * Return: length of string
 */
size_t _strlen(const char *str)
{
	size_t i, count = 0;

	if (str == NULL)
		return (-1);
	for (i = 0; str[i] != '\0'; i++)
		count++;
	return (count);
}

/**
 * _strcpy - copy string to another another memory location
 * @src: source of string to copy
 * @dest: copy string to destination
 * Return: pointer to destination
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	if (src == NULL || dest == NULL)
		return (NULL);
	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
