#include "main.h"
#define BUF_READ 4096
#define INIT_LPTR\
	do {\
		for (i = 0; buf_read[i] != '\n' && buf_read[i] != '\0'; i++)\
			(*lineptr)[i] = buf_read[i];\
		if (buf_read[i] == '\n')\
		{\
			(*lineptr)[i] = '\n';\
			(*lineptr)[++i] = '\0';\
		} \
		else\
			(*lineptr)[i] = '\0';\
		_strcpy(temp, buf_read);\
		for (i = 0; i < count; i++)\
			buf_read[i] = 0;\
		for (i = b_count; temp[i] != '\0'; i++)\
			buf_read[j++] = temp[i];\
	} \
	while (0)

/**
 * _strlen - count the length of string
 * @str: string to count
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


/**
 * _getline - read each line from standard input
 * @lineptr: a storage of the read line
 * @n: size of line pointer
 * @stream: file stream to read from
 * Return: -1 for end of file or error, or read size
 */
ssize_t _getline(char **lineptr, size_t *n, int stream)
{
	static char buf_read[BUF_READ] = "";
	static ssize_t rc = BUF_READ;
	static int nlne = 1;
	char hld_read[BUF_READ / 2] = "", temp[BUF_READ] = "";
	size_t b_count = 0, i, count = BUF_READ, j = 0;

	if (nlne == 0 || buf_read[0] == '\0')
	{
		nlne = 0;
		rc = read(stream, hld_read, sizeof(hld_read));
		_strcat(buf_read, hld_read);
		for (i = 0; buf_read[i] != 0; i++)
			if (buf_read[i] == '\n')
				nlne++;
	}
	if ((rc == -1 && buf_read[0] == '\0') || (rc == 0 && nlne == -1))
		return (-1);
	for (i = 0; buf_read[i] != '\n' && buf_read[i] != '\0'; i++)
		b_count++;
	if (buf_read[i] == '\n')
		b_count++;
	if (*n == 0)
		*lineptr = NULL;
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * (b_count + 1));
		if (*lineptr == NULL)
			return (-1);
	}
	else
	{
		free(*lineptr);
		*lineptr = malloc(sizeof(char) * (b_count + 1));
		if (*lineptr == NULL)
			return (-1);
	}
	*n = b_count;
	INIT_LPTR;
	nlne--;
	return (rc);
}
