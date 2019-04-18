#ifndef _shell_
#define _shell_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
 #include <signal.h>
#define EILLEGALNUMB -2

/**
 * struct GlobalStruct - contains all globals
 * @argv0: first argument when initiating hsh
 * @argv0_len: len of first arg
 * @line: buffer to store command line input
 * @pathTokes: tokenized path array
 * @argTokes: tokenized arg array
 * @last_exit_status: exit status of prev command
 * @prompt_count: prompt count
 * @errstr: error string to pass to perror
 * @error: set to ENOENT standard bur changes if execve executes
 * @interactive: flag to check interactivity
 */
struct GlobalStruct
{
	char *argv0;
	int argv0_len;
	char *line;
	char **pathTokes;
	char **argTokes;
	int last_exit_status;
	int prompt_count;
	char *errstr;
	int error;
	int interactive;
} globes;

/**
 * struct builtin - struct for function pointers
 * @str: str to compare
 * @fptr: function pointer
 */

typedef struct builtin
{
	char *str;
	int (*fptr)(void);
} builtins;

extern char **environ;

void startup(char **argv);
char *_strtok(char *str, char *delim);
void sillyFree(void);
char **tokenizeEnvVar(char *var);
void isInteractiveMode(void);
void handleCommand(char **argv, char **argTokes, char **pathTokes);
char **createTokes(char *str, ssize_t size, char *delim);
int parser(char **argTokes, char **pathTokes);
char *_getenv(const char *name);
void signal_handler(int sig);

/* builtins and caller fctn */
int (*checkBuiltin(char *cmd))(void);
int exitB(void);
int envB(void);

/* general use fctns */
int _strcmp(char *s1, char *s2);
size_t _strlen(char *str);
char *_strcpy(char *dest, const char *src);
char *str_concat(char *s1, char *s2);
void freeTokes(char **tokes);
char *_itoa(int num);
void _rev(char *buff_boi_cpy);
char *_strcat(char *dest, char *src);
long int _atoi(char *str);
long int _pow(int x, int y);

/* error handeling */
char *create_perror_string(char *prompt_count, int pc_len);
void print_error(char *errstr, char *opt, char *prompt_count, int pc_len);
void _error(void);

#endif
