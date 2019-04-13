#ifndef _shell_
#define _shell_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

struct GlobalStruct {
	char *path;
	char *line;
	size_t line_len;
	char *cmd;
	int *prev_status;
	int *prompt_count;
} globes;

typedef struct builtin {
	char *str;
	int (*fptr)(void);
} builtins;

extern char **environ;

char **tokenizeEnvVar(char *var);
void isInteractiveMode(void);
void handleCommand(char **argv, char **argTokes, char **pathTokes);
char **createTokes(char *str, ssize_t size, char *delim);
void parser(char **argTokes, char **pathTokes);
char *_getenv(const char *name);

/* builtins and caller fctn */
int (*checkBuiltin(char *cmd))(void);
int exitB(char *str);
int envB(char *cmd);

/* general use fctns */
int _strcmp(char *s1, char *s2);
size_t _strlen(char *str);
char *_strcpy(char *dest, const char *src);
char *str_concat(char *s1, char *s2);

#endif
