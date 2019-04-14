#include "shell.h"
/**
 * set_error
 *
 * Return:
 */
void set_error(void)
{
	char *prompt_count;
	int pc_len;

	prompt_count = _itoa(globes.prompt_count);
	pc_len = _strlen(prompt_count);
	if (errno == EACCES)
		globes.last_exit_status = 126;
	else if (errno == ENOENT)
	{
		globes.last_exit_status = 127;
		write(STDERR_FILENO, globes.argv0, globes.argv0_len);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, prompt_count, pc_len);
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, globes.argTokes[0], _strlen( globes.argTokes[0]));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "not found\n", 10);
	}
	else
		globes.last_exit_status = 2;
	free (prompt_count);
}
