#include "main.h"

/**
 * str_num - convert string to integer
 * @str: string
 * Return: number
 */
int str_num(char *str)
{
	int num = 0, i = 0, sign = 1;

	if (str[i] == '-')
	{
		i = 1;
		sign = -1;
	}

	for (; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = (num * 10) + (str[i] - '0');
		else
			return (0);
	}
	return (num * sign);
}

/**
 * num_str - convert numbers to string
 * @num: number
 * @str: an pre allocated memory for str
 * Return: pointer to stringed number
 */
char *num_str(int num, char *str)
{
	int i, count = -1, start = 0, m, rem;

	m = num;
	if (num < 0)
	{
		str[0] = '-';
		start = 1;
		count++;
	}
	while (m != 0)
	{
		count++;
		m /= 10;
	}
	str[count + 1] = '\0';
	for (i = count; i >= start; i--)
	{
		rem = num % 10;
	        num /= 10;
		str[i] = rem + '0';
	}
	return (str);
}


/**
 * my_exit - exit from the function
 *
 *
 */
void my_exit(void)
{
	int status = 0;

	if (arc[1] != NULL)
		status = str_num(arc[1]);
	if (status >= 0)
	{
		free_mem(arc, lptr, NULL);
		free_mem(_environ, NULL, NULL);
		exit(status);
	}
	else if (status < 0)
		print_error("Illegal number");
}

/**
 * print_error - print error message
 * @message: message if any
 */
void print_error(char *message)
{
	char *cmd;
	char str[10];
	if (arc != NULL)
	{
		cmd = num_str(commands_cnt, str);

		write(er, argv[0], _strlen(argv[0]));
		write(er, ": ", 2);
		write(er, cmd, _strlen(cmd));
		write(er, ": ", 2);
		if (message == NULL)
			perror(arc[0]);
		else
		{
			write(er, arc[0], _strlen(arc[0]));
			write(er, ": ", 2);
			write(er, message, _strlen(message));
			if (arc[1] != NULL)
			{
				write(er, ": ", 2);
				write(er, arc[1], _strlen(arc[1]));
			}
		}
		if (interactive)
			write(er, "\n", 1);

	}
}

/**
 * print_env - prints environmental variables
 *
 */
void print_env(void)
{
	int i;

	for (i = 0;_environ[i] != NULL; i++)
	{
		write(out, _environ[i], _strlen(_environ[i]));
		write(out, "\n", 1);
	}
}
