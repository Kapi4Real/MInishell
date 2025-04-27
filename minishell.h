#ifndef	minishell_h
#define	minishell_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **g_env;

void set_env_var(char ***env, const char *value, const char *value);
void echo (char **args);
char **copy_env(char **envp);
void free_env(char **envp);
void shell_loop(void);


#endif
