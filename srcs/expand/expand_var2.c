/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:22:51 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 08:16:04 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include <stdbool.h>

static bool	split_here(char quote, bool is_var, int i, char *s)
{
	if (quote)
		return (s[i] == quote);
	if (is_var)
		return (s[i] == '$' || is_delimiter(s[i]));
	return (is_whitespace(s[i]));
}

t_list	*split_in_lst(char *s)
{
	t_list	*first;
	t_list	*tmp;
	char	quote;
	bool	is_var;
	int		i;

	if (!s || !*s)
		return (NULL);
	is_var = (s[0] == '$' && (s[1] == '?' || !is_delimiter(s[1])));
	first = ft_lstnew_empty();
	if (!first)
		return (NULL);
	tmp = first;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (split_here(quote, is_var, i, s))
				quote = (quote ? 0 : s[i]);
			i++;
			continue ;
		}
		if (!quote && split_here(quote, is_var, i, s))
		{
			t_list	*new = ft_lstnew_empty();
			if (!new)
				return (first);
			ft_lstadd_back(&tmp, new);
			tmp = tmp->next;
		}
		else
		{
			char	*new_content = ft_strjoin_char(tmp->content, s[i], true);
			if (new_content)
				tmp->content = new_content;
		}
		i++;
	}
	return (first);
}