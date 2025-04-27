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

void set_env_var(char ***env, const char *value, const char *value)
{
	int count = 0;
	char *new_env = NULL;
	char *new_entry = NULL;
	size_t key_len = strlen(key);

	new_entry = malloc(key_len + strlen(value) + 2);
	if(!new_entry)
	{
		perror("minishell : malloc");
		return ;
	}
	strcpy(new_entry, key);
	strcat(new_entry, "=");
	strcat(new_entry, value);

	while((*env)[count])
		count++;

	new_env = malloc(sizeof(char *) * (count + 2));

	if (!new_env)
	{
		free(new_entry);
		perror("minishell : malloc");
		return ;
	}

	int found = 0;
	int i =0;

	while(i < count)
	{
		if (strncmp((*env)[i], key, key_len) == 0 && (*env)[i][key_len] == "=")
		{
			new_env[i] = new_entry;
			found = 1;
		}
		else
			new_env[i] = (*env)[i];
	}
	if(!found)
	{
		new_env[count] = new_entry;
		new_env[count + 1] = NULL;
	}
	else
	{
		new_env[count] = NULL;
	}
	free(*env);
	*env = new_env;
}

