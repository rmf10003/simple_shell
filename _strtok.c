#include "shell.h"
/**
 * _strtok - tokenize a string
 * @str: string to tokenize
 * @delim: delimiter string
 *
 * Return: pointer to a token
 */
char *_strtok(char *str, char *delim)
{
	static char *placeholder;
	static char oldchar;
	char *token;
	char *d_cpy = delim;

	if (str != NULL)
		placeholder = str;
	else if (oldchar == '\0')
		return (NULL);
	for (; *placeholder != '\0'; placeholder++)
	{
		for (d_cpy = delim; *d_cpy && *d_cpy != *placeholder; d_cpy++)
			;
		if (*d_cpy == '\0')
			break;
	}
	if (*placeholder == '\0')
		return (NULL);
	token = placeholder;
	for (; *placeholder != '\0'; placeholder++)
	{
		for (d_cpy = delim; *d_cpy && *d_cpy != *placeholder; d_cpy++)
			;
		if (*d_cpy != '\0')
			break;
	}
	oldchar = *placeholder;
	*placeholder++ = '\0';
	return (token);
}
