/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	how_many_q(char *arg)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
			nb++;
		i++;
	}
	return (nb);
}

char	*slash_quotes(char *arg)
{
	int		nb_quotes;
	int		i;
	int		y;
	char	*result;

	nb_quotes = how_many_q(arg);
	i = 0;
	y = 0;
	if (!nb_quotes)
		return (arg);
	result = ft_calloc(ft_strlen(arg) + nb_quotes + 1, sizeof(char));
	while (arg[i])
	{
		if (arg[i] == '\"' || arg[i] == '\'')
		{
			result[y] = '\\';
			y++;
		}
		result[y] = arg[i];
		y++;
		i++;
	}
	free(arg);
	return (result);
}

static int	copy_noquote(char *result, char *join, char *quote)
{
	int	i;

	i = 0;
	while (join[i] && ((*quote == 0 && (join[i] == '"' || join[i] == '\''))
			|| (*quote == join[i])))
	{
		if (*quote == 0)
			*quote = join[i];
		else
			*quote = 0;
		i++;
	}
	if (join[i] == '\\' && (join[i + 1] == '\'' || join[i + 1] == '"'))
		i++;
	*result = join[i];
	i++;
	return (i);
}

char	*supp_quotes(char *join)
{
	char	*result;
	char	quote;
	int		i;
	int		y;
	int		len_join;

	len_join = ft_strlen(join);
	result = ft_calloc((len_join + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	y = 0;
	quote = 0;
	while (i < len_join)
	{
		i += copy_noquote(result + y, join + i, &quote);
		y++;
	}
	result[y] = '\0';
	free(join);
	return (result);
}
