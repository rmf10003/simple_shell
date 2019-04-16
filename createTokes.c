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
	_strcpy(cpy, str);
	_strcpy(cpy2, str);
	token = strtok(cpy2, delim);
	if (token == NULL)
	{
		free(cpy);
		free(cpy2);
		return (NULL);
	}
	for (numPtrs = 2; token; numPtrs++)
		token = strtok(NULL, delim);
	free(cpy2);
	tokenArr = malloc(sizeof(char *) * numPtrs);
	if (!tokenArr)
	{
		free(cpy);
		return (NULL);
	}
	*tokenArr++ = cpy;
	token = strtok(cpy, delim);
	for (i = 0; token != NULL; i++)
	{
		tokenArr[i] = token;
		token = strtok(NULL, delim);
	}
	tokenArr[i] = NULL;
	return (tokenArr);
}
