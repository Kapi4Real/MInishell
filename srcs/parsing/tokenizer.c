/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 08:08:08 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:06 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"
#include "libft.h"

#include "parsing.h"
#include "minishell.h"
#include "libft.h"

void skip(char *s, int *i)
{
    while (s[*i] != 0 && (s[*i] == ' ' || s[*i] == '\t'))
        (*i)++;
}

int tokenize_word(t_token **tok_lst, char *val)
{
    int i = 0;
    while (val[i] && !ft_isspace(val[i]) 
           && val[i] != '|' && val[i] != '<' && val[i] != '>')
    {
        if (val[i] == '$' && (val[i+1] == '?' || ft_isalnum(val[i+1]) || val[i+1] == '_'))
        {
            // Crée un token spécial pour les variables
            int start = i;
            i += (val[i+1] == '?') ? 2 : 1;
            while (val[i] && (ft_isalnum(val[i]) || val[i] == '_'))
                i++;
            add_token(tok_lst, 
                create_token(ft_substr(val, start, i - start), EXPAND_VAR));
            continue;
        }
        i++;
    }
    if (i > 0 && val[0] != '$')
        add_token(tok_lst, create_token(ft_substr(val, 0, i), WORD));
    return i;
}



char *expand_var(char *str, t_env *env)
{
    if (str[0] != '$') return ft_strdup(str);
    
    if (str[1] == '?') {
        char *exit_status = ft_itoa(g_exit_status);
        return exit_status;
    }

    char *var_name = str + 1;
    t_env *node = env;
    while (node) {
        if (ft_strcmp(node->name, var_name) == 0)
            return ft_strdup(node->val);
        node = node->next;
    }
    return ft_strdup(""); // Retourne chaîne vide si variable non trouvée
}

void expand_tokens(t_token **tokens, t_env *env)
{
    t_token *tmp = *tokens;
    while (tmp) {
        if (tmp->type == EXPAND_VAR) {
            char *expanded = expand_var(tmp->val, env);
            free(tmp->val);
            tmp->val = expanded;
            tmp->type = WORD;
        }
        tmp = tmp->next;
    }
}

static void add_symbol(t_token **tok_lst, char *symbol, int double_redirect)
{
    if (symbol[0] == '<')
    {
        if (double_redirect == 1)
            add_token(tok_lst, create_token(symbol, HEREDOC));
        else
            add_token(tok_lst, create_token(symbol, INPUT));
    }
    else if (symbol[0] == '>')
    {
        if (double_redirect == 1)
            add_token(tok_lst, create_token(symbol, APPEND));
        else
            add_token(tok_lst, create_token(symbol, OUTPUT));
    }
    else
        add_token(tok_lst, create_token(symbol, PIPE));
}

int tokenize_symbol(t_token **tok_lst, char *val)
{
    char *symbol;
    int i;
    int double_redirect;

    double_redirect = 0;
    if ((val[0] == '<' && val[1] == '<') || (val[0] == '>' && val[1] == '>'))
    {
        double_redirect = 1;
        i = 2;
    }
    else
        i = 1;
    symbol = ft_substr(val, 0, i);
    add_symbol(tok_lst, symbol, double_redirect);
    return i;
}

t_token *tokenizer(char *arg)
{
    int i;
    t_token *token;

    i = 0;
    token = NULL;
    while (arg[i] != 0)
    {
        skip(arg, &i);
        if (arg[i] == '<' || arg[i] == '>' || arg[i] == '|')
            i += tokenize_symbol(&token, arg + i);
        else if (arg[i] != 0)
            i += tokenize_word(&token, arg + i);
    }
    return token;
}
