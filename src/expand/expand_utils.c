/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_list	*ft_lstnew_empty(void)
{
	t_list	*new;

	new = malloc(sizeof (t_list));
	if (!new)
		return (NULL);
	new->content = malloc(sizeof (char));
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->content[0] = '\0';
	new->next = NULL;
	return (new);
}

int	is_env(char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0 && s[i] != '$')
		i++;
	if (s[i] != 0)
		return (1);
	return (0);
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
	if ((c >= 7 && c <= 13) || c == 32)
		return (true);
	return (false);
}

char	*ft_strjoin_char(char *s1, char c, bool free_data)
{
	int		tot_size;
	char	*newchain;
	int		i;

	if (!s1)
		return (NULL);
	tot_size = ft_strlen(s1) + 2;
	newchain = ft_calloc((size_t)tot_size, sizeof(char));
	if (newchain == NULL)
		return (NULL);
	i = 0;
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
