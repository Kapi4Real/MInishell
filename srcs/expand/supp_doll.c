/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supp_doll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 06:37:41 by togomez           #+#    #+#             */
/*   Updated: 2025/05/21 06:38:15 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	is_quote(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

char	*supp_dollars(char *s)
{
	int		i;
	int		y;
	char	*result;
	int		len_join;
	char	quote;

	quote = 0;
	len_join = ft_strlen(s);
	result = ft_calloc((len_join + 1), sizeof(char));
	i = 0;
	y = 0;
	while (i < len_join)
	{
		is_quote(s[i], &quote);
		if (s[i] == '$' && quote == 0 && (s[i + 1] == '\'' || s[i + 1] == '"'))
		{
			quote = s[i + 1];
			i++;
		}
		result[y] = s[i];
		i++;
		y++;
	}
	free(s);
	return (result);
}