/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_cmd(t_cmd *cmd, t_minishell *minish)
{
	int				err;
	t_attributes	attributes;

	if (!cmd->arguments)
		return (0);
	err = fill_attributes(&attributes, cmd->arguments, &minish->envi);
	if (err || attributes.pathname[0] == 0)
	{
		free(attributes.pathname);
		free_achar(attributes.argv);
		free_achar(attributes.envp);
		return (err);
	}
	execve(attributes.pathname, attributes.argv, attributes.envp);
	err = errno;
	if (err == 13)
	{
		str_error_message(attributes.pathname, "Permission denied");
		return (126);
	}
	return (0);
}

int	child(t_cmd *cmd, t_minishell *minish, int stdfd[2])
{
	int	ret_builtin;

	make_redirections(cmd);
	if (cmd->exit_s)
		return (1);
	if (cmd->arguments && is_builtin(cmd->arguments->content))
	{
		ret_builtin = handle_builtin(cmd, minish, stdfd);
		return (ret_builtin);
	}
	else
		return (exec_cmd(cmd, minish));
}

static void	close_unused_fds(t_cmd *cmd)
{
	while (cmd)
	{
		close_and_set(&cmd->input_fd);
		close_and_set(&cmd->output_fd);
		cmd = cmd->next;
	}
}

void	fork_cmd(t_cmd *cmd, t_minishell *minish, int stdfd[2])
{
	int	err;

	cmd->pid = fork();
	if (cmd->pid == -1)
		perror("fork");
	if (cmd->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(stdfd[0]);
		close(stdfd[1]);
		close_unused_fds(cmd->next);
		err = child(cmd, minish, stdfd);
		close_and_set(&cmd->input_fd);
		close_and_set(&cmd->output_fd);
		free_minishell(minish);
		exit(err);
	}
	close_and_set(&cmd->input_fd);
	close_and_set(&cmd->output_fd);
}
