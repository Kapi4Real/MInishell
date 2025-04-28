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

void set_env_var(char ***env, const char *key, const char *value)
{
    int     i;
    int     j;
    size_t  key_len;
    char    *new_entry;
    char    **new_env;

    if (!env || !key || !value)
        return ;
    key_len = strlen(key);
    new_entry = malloc(key_len + strlen(value) + 2);
    if (!new_entry)
        return ;
    sprintf(new_entry, "%s=%s", key, value);
    i = 0;
    while ((*env)[i])
    {
        if (!strncmp((*env)[i], key, key_len) && (*env)[i][key_len] == '=')
            return (free((*env)[i]), (*env)[i] = new_entry, (void)0);
        i++;
    }
    new_env = malloc(sizeof(char *) * (i + 2));
    if (!new_env)
        return (free(new_entry), (void)0);
    j = -1;
    while (++j < i)
        new_env[j] = (*env)[j];
    new_env[i] = new_entry;
    new_env[i + 1] = NULL;
    free(*env);
    *env = new_env;
}

