/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	redirect(int *oldfd, int newfd)
{
	int	fd;

	if (*oldfd == -1)
		return (-1);
	fd = dup2(*oldfd, newfd);
	if (fd == -1)
		perror("dup2");
	close_and_set(oldfd);
	return (fd);
}

int	make_redirections(t_cmd *cmd)
{
	int		err;

	err = 0;
	if (cmd->input_fd != 0)
	{
		err = redirect(&cmd->input_fd, 0);
		if (err == -1)
			return (err);
		cmd->input_fd = 0;
	}
	if (cmd->output_fd != 1)
	{
		err = redirect(&cmd->output_fd, 1);
		if (err == -1)
			return (err);
		cmd->output_fd = 1;
	}
	return (0);
}

int	open_pipe(t_cmd *cmd)
{
	int	pipefd[2];
	int	err;

	pipefd[0] = -1;
	pipefd[1] = -1;
	err = pipe(pipefd);
	if (err == -1)
	{
		perror("pipe");
		return (err);
	}
	if (cmd->output_fd == -1)
		cmd->output_fd = pipefd[1];
	else
		close_and_set(pipefd + 1);
	if (cmd->next->input_fd == -1)
		cmd->next->input_fd = pipefd[0];
	else
		close_and_set(pipefd + 0);
	return (err);
}

int	dup_stdfd(int stdfd[2])
{
	stdfd[0] = dup(0);
	if (stdfd[0] == -1)
	{
		perror("dup2");
		return (1);
	}
	stdfd[1] = dup(1);
	if (stdfd[1] == -1)
	{
		perror("dup2");
		close(stdfd[0]);
		return (1);
	}
	return (0);
}

int	restore_stdfd(int stdfd[2])
{
	int	err;

	err = redirect(stdfd, 0);
	if (err)
		return (1);
	err = redirect(stdfd + 1, 1);
	if (err)
		return (1);
	return (0);
}
