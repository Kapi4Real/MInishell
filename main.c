#include "minishell.h"

char **g_env = NULL;

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	g_env = copy_env(envp);

	if (!g_env)
		return (1);
	shell_loop();

	free_env(g_env);
	return (0); 
}
