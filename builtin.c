#include "shell.h"
/**
 * checkBuiltin - check for built in and run associated command
 * @
 * Return:
 */

int (*checkBuiltin(char *cmd))(void)
{
	int i = 0;
	builtins s_spec[] = {
		/* {"exit", exitB}, */
		/* {"env", envB}, */
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
 * _envB - if command 'env' is passed print environ
 * @cmd: arg[0] from main
 * Return: 1 for success 0 for fail
 */
/* int envB(char *cmd) */
/* { */
/* 	char *env = "env"; */
/* 	char **cpy = environ; */

/* 	for (;*env == *cmd; env++, cmd++) */
/* 	{ */
/* 		if (*env == '\0' && *cmd == '\0') */
/* 		{ */
/* 			while (*cpy != NULL) */
/* 			{ */
/* 				write(1, (*cpy), _strlen(*cpy)); */
/* 				write(1, "\n", 1); */
/* 				cpy++; */
/* 			} */
/* 			return (1); */
/* 		} */
/* 	} */
/* 	return (0); */
/* } */


/**
 * exitB - free allocated stuff and then exit
 * @str: check if "exit"
 * Return:1 on success
 */
/* int exitB(char *str) */
/* { */
/* 	return (0); */
/* } */
