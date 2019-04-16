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
 * Return: 1 on success
 */

int exitB(void)
{
	int manual_exit, i = 1;

	if (globes.argTokes[1] != NULL)
	{
		if (globes.argTokes[1][0] < '0' globes.argTokes[1][0] > '9')
			if (globes.argTokes[1][0] != '+')
				return (2);
		for (; globes.argTokes[1][i]; i++)
			if (globes.argTokes[1][i] < '0' globes.argTokes[1][i] > '9')
				return (2);
		if (_strlen(globes.argTokes[1]) > 11)
			return (2);
		if (globes.argTokes[1][0] == '+')
			manual_exit = _atoi(*(globes.argTokes + 1) + 1);
		else
			manual_exit = _atoi(*globes.argTokes);
	}
	free(globes.line);
	freeTokes(globes.argTokes);
	freeTokes(globes.pathTokes);
	exit(globes.last_exit_status);
}
