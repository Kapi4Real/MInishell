/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:32:10 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:11 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef enum arg_type
{
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
}			t_arg;

typedef struct s_token
{
	t_arg			type;
	char			*val;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	t_list			*arguments;
	t_token			*redirection;
	int				exit_s;
	int				intput_fd;
	int				output_fd;
	__pid_t			pid;
	struct s_cmd	*next;
}				t_cmd;

t_token		*token_new(char *val, t_arg type);
t_token		*token_last(t_token *lst);
t_token		*tokenizer(char *arg);
t_list		*lstlast(t_list *lst);
t_list		*lstnew(char *val);
t_cmd		*cmd_new(void);
t_cmd		*cmd_last(t_cmd *lst);
t_cmd		*cmd(t_token *token);
void		token_clear(t_token *token);
void		token_add_back(t_token **lst, t_token *new);
void		lstadd_back(t_list **lst, t_list *new);
void		lstdelone(t_list *lst);
void		lstclear(t_list **lst);
void		skip(char *s, int *i);
void		cmd_clear(t_cmd **cmd);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
int			check_quotes(char *s);
int			tokenize_word(t_token **tok_lst, char *val);
int			tokenize_symbol(t_token **tok_lst, char *val);
int			test_redirection(t_token **token);
int			test_pipe(t_token **token);
int			parsing(t_token **token);

#endif