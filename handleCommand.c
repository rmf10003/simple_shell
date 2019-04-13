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
	int status;

	pid = fork();
	if (pid == -1)
		perror(argv[0]);
	if (pid == 0)
	{
		parser(argTokes, pathTokes);
		execve(argTokes[0], argTokes, environ);
		perror(argv[0]);
		free(argTokes[-1]);
		free(argTokes - 1);
		free(globes.line);
		exit(1);
	}
	else
		wait(&status);
	free(argTokes[-1]);
	free(argTokes - 1);
	free(pathTokes[-1]);
	free(pathTokes - 1);

}
/**
 * parser - point to "value" in PATH variable | format key=value
 * Description: Tokenize "value" in PATH, concatenate argTokes0 to tokens,
 * check if full_path exists and if it does, set argTokes0 to full_path
 * @argTokes: tokenized input from getline
 * Return: void
 */

void parser(char **argTokes, char **pathTokes)
{
	char *full_path, **cpy = pathTokes;
	int i = 0;
	struct stat st;

	for (i = 0; (*argTokes)[i] != '\0'; i++)
		if ((*argTokes)[i] == '/')
			return;
	for (; *cpy != NULL; cpy++)
	{
		full_path = str_concat(*cpy, *argTokes);
		if (full_path == NULL)
		{
			return;
			/* do something */
		}
		if (stat(full_path, &st) == 0)
		{
			switch (st.st_mode & S_IFMT)
			{
			case S_IFDIR:
				free(full_path);
				break;
			default:
				*argTokes = full_path;
				break;
			}
			break;
		}
		free(full_path);
	}
	free(pathTokes[-1]);
	free(pathTokes - 1);
}
