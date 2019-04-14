#include "shell.h"
/**
 * _rev - reverse a string
 * @buff_boi_cpy: input string
 *
 * Return: nothing
 */
void _rev(char *buff_boi_cpy)
{
	int i, j, k;
	char temp;

	k = _strlen(buff_boi_cpy);
	j = k - 1;
	for (i = 0; i < j; i++, j--)
	{
		temp = buff_boi_cpy[i];
		buff_boi_cpy[i] = buff_boi_cpy[j];
		buff_boi_cpy[j] = temp;
	}
}
/**
 * _itoa - convert integer to char array
 * @num: int to convert
 * @buff_boi: used to store converted char
 *
 * Return: string to be written
 */
char *_itoa(int num)
{
	int i = 0;
	int r;
	int rep = num;
	char* buff_boi;

	buff_boi = malloc(120);
	if (buff_boi == NULL)
		return (NULL);
	if (num < 0)
	{
		num = -num;
	}
	do {
		r = num % 10;
		buff_boi[i] = r + '0';
		num /= 10;
		i++;
	} while (num != 0);
	if (rep < 0)
	{
		buff_boi[i] = '-';
		i++;
	}
	_rev(buff_boi);
	return (buff_boi);
}
