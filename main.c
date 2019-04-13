#include "shell.h"
/**
 * main - hsh
 * @argc: arg count
 * @argv: arg vector
 * Return: EXIT_FAILURE
 */
int main(int argc __attribute__((unused)), char **argv)
{
	char **argTokes;
	char **pathTokes;
	ssize_t read;
	/* int error; */
	int (*bf_ptr)(void);

	while (1)
	{
		isInteractiveMode();
		read = getline(&globes.line, &globes.line_len, stdin);
		if (read == -1)
			break;
		argTokes = createTokes(globes.line, read, " \n\t\r");
		if (argTokes == NULL)
		{
			continue; /* ?? */
		}
		pathTokes = tokenizeEnvVar("PATH");
		if (pathTokes == NULL)
		{
			free(argTokes[-1]);
			free(argTokes - 1);
			continue; /* ?? */
		}
		bf_ptr =  checkBuiltin(argTokes[0]);
		if (bf_ptr == NULL)
			handleCommand(argv, argTokes, pathTokes);
	}
	if (read == -1)
		write(STDERR_FILENO, "\n", 1);
	free(globes.line);
	exit(EXIT_FAILURE);
}
/**
 * isInteractiveMode - check for interactivity?
 *
 * Return:
 */
void isInteractiveMode(void)
{
	if (isatty(STDOUT_FILENO) && isatty(STDIN_FILENO))
	{
		write(STDERR_FILENO, "($) ", 4); /* change prompt */
		globes.prompt_count++;
	}

}
