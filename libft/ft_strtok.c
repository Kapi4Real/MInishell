/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char *save_ptr = NULL;

char	*ft_strtok(char *str, const char *delim)
{
	char	*token_start;
	char	*token_end;
	if (str == NULL)
	{
		if (save_ptr == NULL)
			return (NULL);
		str = save_ptr;
	}
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
	{
		save_ptr = NULL;
		return (NULL);
	}
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	token_end = str;
	if (*token_end != '\0')
	{
		*token_end = '\0';
		save_ptr = token_end + 1;
	}
	else
	{
		save_ptr = NULL;
	}
	return (token_start);
}
