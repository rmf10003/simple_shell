#include "shell.h"
/**
 * set_error
 *
 * Return:
 */
void set_error(void)
{
	if (errno == EACCES)
		globes.last_exit_status = 126;
	else if (errno == ENOENT)
		globes.last_exit_status = 127;
	else
		globes.last_exit_status = 2;
}
