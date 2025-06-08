/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:52:50 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:22:20 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(t_arg type)
{
	return (type == INPUT || type == OUTPUT || type == APPEND || type == HEREDOC);
}

t_cmd	*create_cmd(t_token **tokens)
{
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd || !tokens || !*tokens)
		return (NULL);
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
			ft_lstadd_back(&cmd->arguments,
				ft_lstnew(ft_strdup((*tokens)->val)));
		else if (is_redirection((*tokens)->type))
		{
			token_add_back(&cmd->redirection,
				token_new(ft_strdup((*tokens)->val), (*tokens)->type));
			*tokens = (*tokens)->next;
			if (*tokens && (*tokens)->type == WORD)
				token_add_back(&cmd->redirection,
					token_new(ft_strdup((*tokens)->val), WORD));
		}
		*tokens = (*tokens)->next;
	}
	return (cmd);
}

static void	process_token(t_token *token, t_cmd **commands, t_cmd **current)
{
	t_token	*new_redir;
	t_token	*file;

	if (token->type == WORD)
		ft_lstadd_back(&(*current)->arguments,
			ft_lstnew(ft_strdup(token->val)));
	else if (token->type == PIPE)
	{
		*current = cmd_new();
		cmd_add_back(commands, *current);
	}
	else if (is_redirection(token->type))
	{
		new_redir = token_new(ft_strdup(token->val), token->type);
		token_add_back(&(*current)->redirection, new_redir);
		if (token->next && token->next->type == WORD)
		{
			file = token_new(ft_strdup(token->next->val), WORD);
			token_add_back(&(*current)->redirection, file);
			token = token->next;
		}
	}
}

t_cmd	*cmd(t_token *token)
{
	t_cmd	*commands;
	t_cmd	*current;
	t_token	*tmp;

	if (!token)
		return (NULL);
	current = cmd_new();
	commands = current;
	tmp = token;
	while (tmp)
	{
		process_token(tmp, &commands, &current);
		tmp = tmp->next;
	}
	return (commands);
}