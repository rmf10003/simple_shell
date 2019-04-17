#include "shell.h"

/**
 * createTokes - tokenize str without damaging original string
 * Description: Create a copy of str, break copy into tokens,
 * store tokens in array args (null terminated)
 * @str: string to be tokenized
 * @size: length of original string
 * @delim: string of delimiters specified by the caller
 * Return: double pointer to array of strings named args
 */

char **createTokes(char *str, ssize_t size, char *delim)
{
	char **tokenArr, *cpy, *cpy2, *token;
	int numPtrs, i;

	cpy = malloc(size + 1);
	if (!cpy)
		return (NULL);
	cpy2 = malloc(size + 1);
	if (!cpy2)
	{
		free(cpy);
		return (NULL);
	}
	_strcpy(cpy, str), _strcpy(cpy2, str);
	token = _strtok(cpy2, delim);
	for (numPtrs = 2; token; numPtrs++)
	{
		if (*token == '#')
			break;
		token = _strtok(NULL, delim);
       	}
	if (numPtrs == 2)
	{
		free(cpy), free(cpy2);
		return (NULL);
	}
	free(cpy2);
	tokenArr = malloc(sizeof(char *) * numPtrs);
	if (!tokenArr)
	{
		free(cpy);
		return (NULL);
	}
	*tokenArr++ = cpy, token = _strtok(cpy, delim);
	for (i = 0; i < (numPtrs - 2); i++)
	{
		tokenArr[i] = token;
		token = _strtok(NULL, delim);
	}
	tokenArr[i] = NULL;
	return (tokenArr);
}
