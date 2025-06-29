/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <linux/limits.h>

bool	is_builtin(const char *s);
int		handle_builtin(t_cmd *cmd, t_minishell *minish, int stdfd[2]);

int		echo(t_cmd *cmd);

int		cd(t_cmd *cmd, t_env **envi);

int		pwd(void);

int		export(t_env *envi);
int		export_add(t_env **envi, t_list *args);
char	**sep_on_equal(char *s);
int		export_join(t_env **envi, char *s);
int		set_null(t_env **envi, char *s);
int		export_update(t_env **envi, char *s);

void	unset(t_env *envi, t_list *args);

int		env(t_env *envi);

int		__exit(t_minishell *minish, t_list *args, int stdfd[2]);

#endif
