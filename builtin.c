#include "shell.h"
/**
 * checkBuiltin - check for built in and run associated command
 * @cmd: global argtok0
 * Return: integer
 */

int (*checkBuiltin(char *cmd))(void)
{
	int i = 0;
	builtins s_spec[] = {
		{"exit", exitB},
		{"env", envB},
		/* {"cd", cdB}, */
		/* {"setenv", setenvB}, */
		/* {"unsetenv", unsetenvB}, */
		/* {"help", helpB}, */
		/* {"history", historyB}, */
		{NULL, NULL}
	};

	while (s_spec[i].str != NULL)
	{
		if (_strcmp(s_spec[i].str, cmd) == 0)
			return (s_spec[i].fptr);
		i++;
	}
	return (NULL);
}

/**
 * envB - if command 'env' is passed print environ
 * Description: print out environment list
 * Return: 1 for success 0 for fail
 */

int envB(void)
{
	char **cpy = environ;

	while (*cpy != NULL)
	{
		write(1, (*cpy), _strlen(*cpy));
		write(1, "\n", 1);
		cpy++;
	}
	return (0);
}

/**
 * exitB - free allocated stuff and then exit
 * Return: 2 on failure
 */

int exitB(void)
{
	long int manual_exit, i = 1;

	if (globes.argTokes[1] != NULL)
	{
		if (globes.argTokes[1][0] < '0' || globes.argTokes[1][0] > '9')
			if (globes.argTokes[1][0] != '+')
			{
				errno = EILLEGALNUMB;
				_error();
				return (2);
			}
		for (; globes.argTokes[1][i]; i++)
			if (globes.argTokes[1][i] < '0' && globes.argTokes[1][i] > '9')
			{
				errno = EILLEGALNUMB;
				_error();
				return (2);
			}
		if (_strlen(globes.argTokes[1]) > 11)
		{
			errno = EILLEGALNUMB;
			_error();
			return (2);
		}
		if (globes.argTokes[1][0] == '+')
			manual_exit = _atoi(&globes.argTokes[1][1]);
		else
			manual_exit = _atoi(globes.argTokes[1]);
		if (manual_exit > 2147483647l)
		{
			errno = EILLEGALNUMB;
			_error();
			return (2);
		}
		free(globes.line);
		freeTokes(globes.argTokes);
		freeTokes(globes.pathTokes);
		exit(manual_exit & 0377);
	}
	else
	{
		free(globes.line);
		freeTokes(globes.argTokes);
		freeTokes(globes.pathTokes);
		exit(globes.last_exit_status);
	}
}

/**
 * _atoi - convert a char array into an int
 * @str: char string to convert
 *
 * Return: integer rep of char str
 */
long int _atoi(char *str)
{
	long int exit_status = 0;
	int i = 0;
	char *cpy = str;

	for (; cpy[i]; i++)
		;
	i--;
	for (; *cpy; cpy++, i--)
		exit_status += (*cpy - '0') * _pow(10, i);
	return (exit_status);
}
/**
 * _pow - returns val of x raised to y
 * @x: base int
 * @y: power int
 *
 * Return: val of x raised to y
 */
long int _pow(int x, int y)
{
	if (y < 0)
		return (-1);
	else if (y == 0)
		return (1);
	else
		return (x * _pow(x, y - 1));
}
