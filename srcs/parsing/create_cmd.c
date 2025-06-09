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

static char *get_env_value(char *var, t_env *env);

t_cmd	*create_cmd(t_token **tokens, t_env *env)
{
	t_cmd	*cmd;

	cmd = cmd_new();
	if (!cmd || !tokens || !*tokens)
		return (NULL);
	while (*tokens && (*tokens)->type != PIPE)
	{
		if ((*tokens)->type == WORD)
		{
			char *expanded = expand_vars_in_string((*tokens)->val, env);
			ft_lstadd_back(&cmd->arguments, ft_lstnew(expanded));
		}
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

char *expand_vars_in_string(char *str, t_env *env)
{
    char *result = ft_strdup("");
    int i = 0;
    int in_quote = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_quote)
            in_quote = 1;
        else if (str[i] == '\'' && in_quote)
            in_quote = 0;

        if (str[i] == '$' && !in_quote && (str[i+1] == '?' || ft_isalnum(str[i+1])))
        {
            int start = ++i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                i++;
            char *var = ft_substr(str, start, i - start);
            char *value = get_env_value(var, env);
            char *new_result = ft_strjoin(result, value);
            free(result);
            free(var);
            free(value);
            result = new_result;
            continue;
        }
        else
        {
            char c[2] = {str[i++], 0};
            char *new_result = ft_strjoin(result, c);
            free(result);
            result = new_result;
        }
    }
    return result;
}

char *get_env_value(char *var, t_env *env)
{
    if (ft_strcmp(var, "?") == 0)
        return ft_itoa(g_exit_status);

    t_env *tmp = env;
    while (tmp)
    {
        if (ft_strcmp(tmp->name, var) == 0)
            return ft_strdup(tmp->val);
        tmp = tmp->next;
    }
    return ft_strdup("");
}

static void process_token(t_token *token, t_cmd **commands, t_cmd **current, t_env *env)
{
    if (token->type == WORD)
    {
        char *expanded = expand_vars_in_string(token->val, env);
        char *without_quotes = remove_quotes(expanded,env);
        free(expanded);
        ft_lstadd_back(&(*current)->arguments, ft_lstnew(without_quotes));
    }
    else if (token->type == PIPE)
    {
        *current = cmd_new();
        cmd_add_back(commands, *current);
    }
    else if (is_redirection(token->type))
    {
        char *expanded_redir = expand_vars_in_string(token->val, env);
        char *without_quotes_redir = remove_quotes(expanded_redir,env);
        free(expanded_redir);
        t_token *new_redir = token_new(without_quotes_redir, token->type);
        token_add_back(&(*current)->redirection, new_redir);

        if (token->next && token->next->type == WORD)
        {
            char *expanded_file = expand_vars_in_string(token->next->val, env);
            char *without_quotes_file = remove_quotes(expanded_file,env);
            free(expanded_file);
            t_token *file = token_new(without_quotes_file, WORD);
            token_add_back(&(*current)->redirection, file);
            token = token->next;
        }
    }
}

t_cmd *cmd(t_token *token, t_env *env)
{
    t_cmd *commands;
    t_cmd *current;
    t_token *tmp;

    if (!token)
        return (NULL);
    current = cmd_new();
    commands = current;
    tmp = token;
    while (tmp)
    {
        process_token(tmp, &commands, &current, env);
        tmp = tmp->next;
    }
    return (commands);
}
