/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 12:00:00 by user              #+#    #+#             */
/*   Updated: 2023/05/01 12:00:00 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **copy_env(char **envp)
{
    int count = 0;
    while (envp[count]) count++;
    
    char **new_env = malloc(sizeof(char *) * (count + 1));
    if (!new_env) return NULL;
    
    for (int i = 0; envp[i]; i++) {
        new_env[i] = ft_strdup(envp[i]);
        if (!new_env[i]) {
            free_array(new_env);
            return NULL;
        }
    }
    new_env[count] = NULL;
    return new_env;
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

char	*get_env_var(char **envp, const char *name)
{
	int		i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], name, name_len) == 0)
			&& envp[i][name_len] == '=')
			return (&envp[i][name_len + 1]);
		i++;
	}
	return (NULL);
}

void set_env_var(char ***env, const char *key, const char *value)
{
    int i;
    char *new_var;
    
    if (!key || !value) return;
    
    new_var = malloc(strlen(key) + strlen(value) + 2);
    if (!new_var) return;
    sprintf(new_var, "%s=%s", key, value);
    
    for (i = 0; (*env)[i]; i++) {
        if (strncmp((*env)[i], key, strlen(key)) == 0 && 
            (*env)[i][strlen(key)] == '=') {
            free((*env)[i]);
            (*env)[i] = new_var;
            return;
        }
    }
    
    int count = 0;
    while ((*env)[count]) count++;
    
    char **new_env = realloc(*env, (count + 2) * sizeof(char *));
    if (!new_env) {
        free(new_var);
        return;
    }
    
    new_env[count] = new_var;
    new_env[count + 1] = NULL;
    *env = new_env;
}

void	init_env(char **envp)
{
	int	count;
	int	i;

	count = 0;
	while (envp[count])
		count++;
	g_env = malloc(sizeof(char *) * (count + 1));
	if (!g_env)
		return ;
	i = 0;
	while (envp[i])
	{
		g_env[i] = ft_strdup(envp[i]);
		if (!g_env[i])
		{
			while (i > 0)
				free(g_env[--i]);
			free(g_env);
			return ;
		}
		i++;
	}
	g_env[count] = NULL;
}
