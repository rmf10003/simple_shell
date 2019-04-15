#include "shell.h"
/**
 * handleCommand - see if executable exists, if so runs it, if not handle error
 * @argv: initial hsh call and arguments passed through main
 * @argTokes: tokenized command line str
 * @pathTokes: tokenized copy of the path
 * Return: void??
 */
void handleCommand(char **argv, char **argTokes, char **pathTokes)
{
	pid_t pid;
	int status, p_success;

	pid = fork();
	if (pid == -1)
		perror(argv[0]);
	if (pid == 0)
	{
		if ((p_success = parser(argTokes, pathTokes)) == 0)
		{
			execve(argTokes[0], argTokes, environ);
			globes.error = errno;
		}
		errno = globes.error;
		if (p_success != -2)
			_error();
		freeTokes(globes.pathTokes);
		freeTokes(globes.argTokes);
		free(globes.line);
		exit(globes.last_exit_status);
	}
	else
	{
		wait(&status);
		globes.last_exit_status = WEXITSTATUS(status);
	}
	freeTokes(globes.argTokes);
	freeTokes(globes.pathTokes);

}
/**
 * parser - point to "value" in PATH variable | format key=value
 * Description: Tokenize "value" in PATH, concatenate argTokes0 to tokens,
 * check if full_path exists and if it does, set argTokes0 to full_path
 * @argTokes: tokenized input from getline
 * Return: void
 */

int parser(char **argTokes, char **pathTokes)
{
	char *full_path, **cpy = pathTokes;
	int i, dir = 0;
	struct stat st;

	for (i = 0; (*argTokes)[i] != '\0'; i++)
		if ((*argTokes)[i] == '/')
		{
			/* execve(argTokes[0], argTokes, environ); */
			return (0);
		}
	for (; *cpy != NULL; cpy++)
	{
		full_path = str_concat(*cpy, *argTokes);
		if (full_path == NULL)
		{
			return (-1);
		}
		if (stat(full_path, &st) == 0)
		{
			switch (st.st_mode & S_IFMT)
			{
			case S_IFDIR:
				free(full_path);
				dir = 1;
				break;
			default:
				*argTokes = full_path;
				/* execve(argTokes[0], argTokes, environ); */
				break;
			}
			break;
		}
		else if (errno == ENAMETOOLONG)
			globes.error = errno;
		free(full_path);
	}
	if (*cpy == NULL)
		return (-1);
	if (dir)
		return (-2);
	return (0);
}
