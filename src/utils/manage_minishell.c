/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_minishell(t_minishell *minishell, int ac, char **av, char **ep)
{
	(void) ac;
	(void) av;
	(*minishell).commands = NULL;
	(*minishell).envi = envp_to_lst(ep);
	(*minishell).exit_status = 0;
	(*minishell).n_line = 1;
}

void	close_mini_fds(t_cmd *cmd)
{
	while (cmd)
	{
		close_and_set(&cmd->input_fd);
		close_and_set(&cmd->output_fd);
		cmd = cmd->next;
	}
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->commands)
		cmd_clear(&minishell->commands);
	if (minishell->envi)
		env_clear(minishell->envi);
}
