#include "minishell.h"

char **copy_env(char **envp)
{
	int		count;
	int		i;
	char	**new_env;

	count = 0;
	i = 0;	
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char * ) * (count +1));

	if (!new_env)
		return (NULL);

	while (envp[i])
	{
		new_env[i] = strdup(envp[i]);
		if (!new_env[i])
		{
			while (i > 0)
			{
				free(new_env[i]);
				i--;
			}
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[count] = NULL;
	return (new_env);
}

void free_env(char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return ;

	while(envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char *get_env_var(char **envp, const char *name)
{
	int i;
	size_t name_len;

	i = 0;
	name_len = strlen(name);

	while (envp[i])
	{
		if ((strncmp(envp[i], name, name_len) == 0) && envp[i][name_len] == '=')
			return(&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

void shell_loop(void)
{
	printf("USER=%s\n", get_env_var(g_env, "USER"));
	printf("PWD=%s\n", get_env_var(g_env, "PWD"));

}
