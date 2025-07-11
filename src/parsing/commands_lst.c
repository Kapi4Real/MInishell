/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*cmd_new(void)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->arguments = NULL;
	new->redirections = NULL;
	new->exit_s = 0;
	new->input_fd = -1;
	new->output_fd = -1;
	return (new);
}

t_cmd	*cmd_last(t_cmd *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	cmd_add_back(t_cmd **lst, t_cmd *new)
{
	if (!lst || !new)
		return ;
	if (*lst)
		cmd_last(*lst)->next = new;
	else
		*lst = new;
}

void	cmd_clear(t_cmd	**cmd)
{
	if (!cmd || !*cmd)
		return ;
	if ((*cmd)->next)
		cmd_clear(&(*cmd)->next);
	if ((*cmd)->arguments)
		lstclear(&(*cmd)->arguments);
	if ((*cmd)->redirections)
		token_clear((*cmd)->redirections);
	free(*cmd);
	*cmd = NULL;
}
