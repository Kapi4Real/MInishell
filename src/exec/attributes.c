/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attributes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**arglst_to_argv(t_list *arguments)
{
	char	**argv;
	int		size;
	int		i;

	size = ft_lstsize(arguments);
	argv = malloc((size + 1) * sizeof (char *));
	if (!argv)
		return (NULL);
	i = 0;
	while (i < size)
	{
		argv[i] = ft_strdup(arguments->content);
		arguments = arguments->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

static char	*env_find(t_env *envi, char *to_find)
{
	while (envi && (ft_strcmp(envi->name, to_find)))
		envi = envi->next;
	if (!envi)
		return (NULL);
	return (envi->val);
}

void	free_attributes(t_attributes attributes)
{
	free(attributes.pathname);
	free_achar(attributes.argv);
	free_achar(attributes.envp);
}

int	fill_attributes(t_attributes *attributes, t_list *args, t_env **envi)
{
	char	*env_path;
	int		ret;

	attributes->envp = envlst_to_envp(envi);
	if (!attributes->envp)
		return (1);
	attributes->argv = arglst_to_argv(args);
	if (!attributes->argv)
	{
		free_achar(attributes->envp);
		return (1);
	}
	env_path = env_find(*envi, "PATH");
	attributes->pathname = ft_strdup(attributes->argv[0]);
	ret = check_name(&attributes->pathname, env_path);
	if (!attributes->pathname)
	{
		free_achar(attributes->envp);
		free_achar(attributes->argv);
	}
	return (ret);
}
