#include "shell.h"

/**
 * _strcpy - copy from src into dest
 * @dest: string to copy into
 * @src: string to copy
 * Return: pointer to dest
 */

char *_strcpy(char *dest, const char *src)
{
	char *dest_cpy = dest;

	if (!dest || !src)
		return (NULL);
	for (; *src; src++, dest_cpy++)
		*dest_cpy = *src;
	*dest_cpy = '\0';
	return (dest);
}

/**
 * _strlen - find length of string
 * @str: pointer to incoming string
 * Return: string length
 */

size_t _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}

/**
 * str_concat - concatenates two strings
 * @s1: pointer to string 1
 * @s2: pointer to string 2
 * Return: pointer to malloc'd space containing concatenated string
 */

char *str_concat(char *s1, char *s2)
{
	char *cat_str, *cpy1, *cpy2;
	int count1 = 0;
	int count2 = 0;
	int i = 0;
	int j;
	int forward_slash = 0;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	cpy1 = s1;
	cpy2 = s2;
	for (; *cpy1; cpy1++, count1++)
		;
	if (*(cpy1 - 1) != '/')
		count1++, forward_slash = 1;
	for (; *cpy2; cpy2++, count2++)
		;
	count2++;
	cat_str = malloc(sizeof(*s1) * count1 + sizeof(*s2) * count2);
	if (cat_str == NULL)
		return (cat_str);
	for (; s1[i]; i++)
		cat_str[i] = s1[i];
	if (forward_slash)
		cat_str[i++] = '/';
	for (j = 0; j < count2; i++, j++)
		cat_str[i] = s2[j];
	return (cat_str);
}

/**
 * _strcmp - compares two strings
 * @s1: points to string 1
 * @s2: points to string 2
 * Return: 0 on success, any other number on failure
 */

int _strcmp(char *s1, char *s2)
{
	int x = 0;

	for (; *s1 || *s2; s1++, s2++)
		if (*s1 != *s2)
		{
			x = *s1 - *s2;
			break;
		}
	return (x);
}
/**
 * *_strcat - concatenates two strings
 * @dest: points to address char string
 * @src: points to address char string
 *
 * Return: pointer to char string dest
 */
char *_strcat(char *dest, char *src)
{
	char *cptr = dest;

	while (*cptr)
	{
		cptr++;
	}
	while (*src)
	{
		*cptr = *src;
		cptr++;
		src++;
	}
	return (dest);
}
