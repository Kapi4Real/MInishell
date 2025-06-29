/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	redirect_tester(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type != WORD)
		return (0);
	return (1);
}

int	pipe_tester(t_token **token)
{
	if ((*token)->next == NULL || (*token)->next->type == PIPE)
		return (0);
	return (1);
}

int	parsing(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE && !pipe_tester(&tmp))
			return (0);
		else if (tmp->type != PIPE && tmp->type != WORD
			&& !redirect_tester(&tmp))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
