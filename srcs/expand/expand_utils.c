/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 09:57:07 by togomez           #+#    #+#             */
/*   Updated: 2025/05/06 11:22:17 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

t_list	*ft_lstnew_empty(void)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = malloc(1);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	((char *)new->content)[0] = '\0';
	new->next = NULL;
	return (new);
}

int	is_env(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != '$')
		i++;
	return (s[i] != 0);
}

bool	is_delimiter(char c)
{
	if (ft_isalnum(c))
		return (false);
	if (c == '_')
		return (false);
	return (true);
}

bool	is_whitespace(char c)
{
	return ((c >= 7 && c <= 13) || c == 32);
}

char	*ft_strjoin_char(char *s1, char c, bool free_data)
{
	int		tot_size;
	char	*newchain;
	int		i;

	tot_size = ft_strlen(s1) + 2;
	newchain = ft_calloc(tot_size, sizeof(char));
	i = 0;
	if (!newchain)
		return (NULL);
	while (s1[i])
	{
		newchain[i] = s1[i];
		i++;
	}
	newchain[i++] = c;
	newchain[i] = 0;
	if (free_data)
		free(s1);
	return (newchain);
}

int	env_var_exists(char *var, int len, t_env *envi)
{
	while (envi)
	{
		if (ft_strncmp(envi->name, var, len) == 0 && envi->name[len] == '\0')
			return (1);
		envi = envi->next;
	}
	return (0);
}