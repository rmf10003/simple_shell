#include "shell.h"

/**
 * tokenizeEnvVar - tokenize specified env variable
 * @var: environmental variable
 * Return: array of tokenized strings
 */

char **tokenizeEnvVar(char *var)
{
	char **tokes;
	char *var_str;
	int len;

	var_str = _getenv(var);

	len = _strlen(var_str);
	tokes = createTokes(var_str, len, ":");
	return (tokes);
}

/**
 * _getenv - searches the environment list (array of strings) to find the
 * environment variable name and returns a pointer to the corresponding value
 * @name: for our purposes will be "PATH"
 * Return: pointer to the value string
 */

char *_getenv(const char *name)
{
	char const *name_cpy;
	char **cpy = environ;

	while (*cpy != NULL)
	{
		name_cpy = name;
		while (**cpy == *name_cpy)
			name_cpy++, (*cpy)++;
		if (*name_cpy == '\0' && **cpy == '=')
		{
			(*cpy) -= 4;
			return ((*cpy) + 5);
		}
		cpy++;
	}
	return (NULL);
}
