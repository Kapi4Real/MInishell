/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*envp_to_lst(char **env_var)
{
	int		i;
	int		secure;
	t_env	*env_lst;
	char	**current_var;

	i = 0;
	env_lst = NULL;
	while (env_var[i] != 0)
	{
		secure = 0;
		current_var = sep_on_equal(env_var[i]);
		while (current_var[secure])
			secure++;
		if (secure > 1)
			env_add_back(&env_lst, env_new(ft_strdup(current_var[0]),
					ft_strdup(current_var[1])));
		i++;
		free_split(current_var);
	}
	return (env_lst);
}
