#include "shell.h"
/**
 * main - hsh
 * @argc: arg count
 * @argv: arg vector
 * Return: EXIT_FAILURE
 */
int main(int argc __attribute__((unused)), char **argv)
{
	ssize_t read;
	size_t len;
	/* int error; */
	int (*bf_ptr)(void);

	globes.argv0 = *argv;
	globes.argv0_len = _strlen(*argv);

	while (1)
	{
		errno = 0;
		isInteractiveMode();
		read = getline(&globes.line, &len, stdin);
		if (read == -1)
			break;
		globes.argTokes = createTokes(globes.line, read, " \n\t\r");
		if (globes.argTokes == NULL)
		{
			continue; /* ?? */
		}
		globes.pathTokes = tokenizeEnvVar("PATH");
		if (globes.pathTokes == NULL)
		{
			freeTokes(globes.argTokes);
			continue; /* ?? */
		}
		bf_ptr = checkBuiltin(globes.argTokes[0]);
		if (bf_ptr != NULL)
		{
			globes.last_exit_status = bf_ptr();
			freeTokes(globes.argTokes);
			freeTokes(globes.pathTokes);
		}
		else
			handleCommand(argv, globes.argTokes, globes.pathTokes);
	}
	if (read == -1)
		write(STDERR_FILENO, "\n", 1);
	free(globes.line);
	exit(globes.last_exit_status);
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
/**
 *
 *
 * Return:
 */
void freeTokes(char **tokes)
{
	free(tokes[-1]);
	free(tokes - 1);
}
