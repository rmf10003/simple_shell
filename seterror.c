#include "shell.h"

/**
 * _error - handle errors
 */

void _error(void)
{
	char *prompt_count;
	int pc_len;

	prompt_count = _itoa(globes.prompt_count);
	pc_len = _strlen(prompt_count);
	if (errno == EILLEGALNUMB)
		print_error("Illegal number: ", globes.argTokes[1], prompt_count, pc_len);
	else if (errno == ENOENT || errno == ENOTDIR)
	{
		if (errno == ENOENT)
			globes.last_exit_status = 127;
		else
			globes.last_exit_status = 2;
		print_error("not found\n", NULL, prompt_count, pc_len);
	}
	else
	{
		if (errno == EACCES)
			globes.last_exit_status = 126;
		else
			globes.last_exit_status = 2;
		create_perror_string(prompt_count, pc_len);
		perror(globes.errstr);
		if (globes.errstr != NULL)
			free(globes.errstr);
	}
	free(prompt_count);
}

/**
 * print_error - print proper error message
 * @errstr: error message
 * @opt: optional string
 * @prompt_count: prompt count string
 * @pc_len: length of pc str
 * Return: void
 */

void print_error(char *errstr, char *opt, char *prompt_count, int pc_len)
{
	write(STDERR_FILENO, globes.argv0, globes.argv0_len);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, prompt_count, pc_len);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, globes.argTokes[0], _strlen(globes.argTokes[0]));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, errstr, _strlen(errstr));
	if (opt != NULL)
	{
		write(STDERR_FILENO, opt, _strlen(opt));
		write(STDERR_FILENO, "\n", 1);
	}
}

/**
 * create_perror_string - stuff
 * @prompt_count: prompt count string
 * @pc_len: length of pc str
 * Return: pointer to string
 */

char *create_perror_string(char *prompt_count, int pc_len)
{
	int msize = 5;
	int j = 0;

	msize += globes.argv0_len + pc_len + _strlen(globes.argTokes[0]);
	globes.errstr = malloc(msize);
	if (globes.errstr == NULL)
		return (NULL);
	for (; j < msize; j++)
		globes.errstr[j] = '\0';
	_strcat(globes.errstr, globes.argv0);
	_strcat(globes.errstr, ": ");
	_strcat(globes.errstr, prompt_count);
	_strcat(globes.errstr, ": ");
	_strcat(globes.errstr, globes.argTokes[0]);
	return (globes.errstr);
}
