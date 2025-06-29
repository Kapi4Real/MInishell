/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <stdbool.h>
# include <minishell.h>

typedef struct s_minishell	t_minishell;

typedef struct s_env
{
	char			*name;
	char			*val;
	struct s_env	*next;
}					t_env;

t_env	*env_new(char	*var_name, char *var_val);
t_env	*env_last(t_env *lst);
void	env_add_back(t_env **lst, t_env *new);
void	env_clear(t_env	*lst);
int		env_size(t_env *env);
t_env	*envp_to_lst(char **env_var);
int		is_env(char *s);

void	handle_word(char *s, t_env *envi, t_list **new, int exit_status);

char	*ft_strjoin_char(char *s1, char c, bool free_data);
bool	is_delimiter(char c);
t_list	*ft_lstnew_empty(void);
char	*supp_quotes(char *join);
char	*slash_quotes(char *arg);
bool	is_whitespace(char c);
t_list	*split_on_whitespace(char *s);
t_list	*split_in_lst(char *s);
int		expand_red(t_token *red, t_env *env, int exit_status);
void	expand_var(t_minishell *minishell, int exit_s);
char	*supp_dollars(char *s);
bool	check_heredoc_quote(t_cmd *cmd);

void	handle_heredoc(char *s, int *fd, int *exit_s, int n_line);
void	red_treatment(t_minishell *minishell);
void	heredoc_treatment(t_minishell *minishell);

#endif
