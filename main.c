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
	int (*bf_ptr)(void);

	globes.error = ENOENT;
	globes.argv0 = *argv;
	globes.argv0_len = _strlen(*argv);
	signal(SIGINT, &signal_handler);
	while (1)
	{
		isInteractiveMode();
		read = getline(&globes.line, &len, stdin);
		if (read == -1)
			break;
		globes.prompt_count++;
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
	if (read == -1 && globes.interactive)
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
		globes.interactive = 1;
		write(STDERR_FILENO, "$ ", 2); /* change prompt */
	}

}

/**
 * freeTokes - stuff
 * Description: stuff
 * @tokes: free tokens
 * Return: void
 */

void freeTokes(char **tokes)
{
	free(tokes[-1]);
	free(tokes - 1);
}

/**
 * signal_handler - handle signal
 * @sig: SIGINT
 * Return: void
 */

void signal_handler(int sig __attribute__((unused)))
{
	write(STDERR_FILENO, "\n$ ", 3);
}
