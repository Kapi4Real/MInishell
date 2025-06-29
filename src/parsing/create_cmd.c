/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_token(t_token **token, t_cmd **commands, t_cmd **current)
{
	t_token	*new;
	t_token	*prev;

	if ((*token)->type == WORD)
		lstadd_back(&(*current)->arguments, lstnew((*token)->val));
	else if ((*token)->type == PIPE)
	{
		free((*token)->val);
		(*current) = cmd_new();
		cmd_add_back(commands, (*current));
	}
	else
	{
		new = token_new((*token)->next->val, (*token)->type);
		token_add_back(&(*current)->redirections, new);
		prev = *token;
		*token = (*token)->next;
		free(prev->val);
		free(prev);
	}
}

t_cmd	*cmd(t_token *token)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_token	*prev;

	commands = NULL;
	if (token)
	{
		current = cmd_new();
		cmd_add_back(&commands, current);
	}
	while (token)
	{
		add_token(&token, &commands, &current);
		prev = token;
		token = token->next;
		free(prev);
	}
	return (commands);
}
