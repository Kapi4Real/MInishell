/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: togomez <togomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 07:51:36 by togomez           #+#    #+#             */
/*   Updated: 2025/04/25 11:21:08 by togomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(const char *s)
{
	int	len;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (len < 2)
		return (ft_strdup(s));
	if ((s[0] == '\'' && s[len - 1] == '\''))
		return (ft_substr(s, 1, len - 2));
	if ((s[0] == '"' && s[len - 1] == '"'))
		return (ft_substr(s, 1, len - 2));
	return (ft_strdup(s));
}
