/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:39:17 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:12 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
# include "stdio.h"
# include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char **g_env;

void set_env_var(char ***env, const char *key, const char *value);
void echo (char **args);
char **copy_env(char **envp);
void free_env(char **envp);
void shell_loop(void);
int    exec_commands(t_cmd *cmds, char **envp);
int    exec_commands(t_cmd *cmds, char **envp);
char  *find_executable(char *cmd, char **envp);
int    handle_redirections(t_cmd *cmd);
int exec_commands(t_cmd *cmds, char **envp);
int handle_redirections(t_cmd *cmd);
int is_builtin(char *cmd);
int run_builtin(t_cmd *cmd);
char *find_executable(char *cmd, char **envp);




#endif
