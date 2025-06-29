/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include <parsing.h>
# include <expand.h>
# include <exec.h>
# include <builtins.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/ioctl.h>

typedef struct s_minishell
{
	t_cmd	*commands;
	t_env	*envi;
	int		exit_status;
	int		n_line;
}			t_minishell;

void	init_minishell(t_minishell *minishell, int ac, char **av, char **ep);
void	close_mini_fds(t_cmd *cmd);
void	free_minishell(t_minishell *minishell);

void	free_achar(char **achar);

void	error_message(char *path, int err);
void	str_error_message(char *name, char *err);

int		str_skip_to_char(char *str, char c);
int		str_skip_to_any_char(char *str, char *targets);
int		str_skip_char(char *str, char c);
void	free_split(char **split);

#endif
