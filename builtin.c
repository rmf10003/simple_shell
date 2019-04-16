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
	free(globes.line);
	freeTokes(globes.argTokes);
	freeTokes(globes.pathTokes);
	exit(globes.last_exit_status);
}
