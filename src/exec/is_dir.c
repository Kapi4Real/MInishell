/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_dir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_path(char *str)
{
	int	i;

	if (str[0] == '/' || ft_strncmp(str, "./", 2) == 0)
		return (1);
	i = 1;
	while (str[i])
	{
		if (str[i] == '/' && str[i - 1] != '\\')
			return (1);
		i++;
	}
	return (0);
}

int	is_dir(char *str, int print_error)
{
	struct stat	buf;
	int			dir;

	if (stat(str, &buf) != 0)
	{
		if (print_error)
			str_error_message(str, strerror(errno));
		return (1);
	}
	dir = S_ISDIR(buf.st_mode);
	if (dir)
		str_error_message(str, "Is a directory");
	return (dir);
}

static int	stat_exit_code(int err)
{
	if (err == 13)
		return (126);
	return (125 + err);
}

static int	file_status(char *str)
{
	struct stat	buf;
	int			err;

	if (stat(str, &buf) != 0)
	{
		err = errno;
		str_error_message(str, strerror(err));
		return (stat_exit_code(err));
	}
	if (S_ISDIR(buf.st_mode))
	{
		str_error_message(str, "Is a directory");
		return (126);
	}
	else if ((buf.st_mode & (S_IRUSR | S_IXUSR)) != (S_IRUSR | S_IXUSR))
	{
		str_error_message(str, "Permission denied");
		return (126);
	}
	return (0);
}

int	check_name(char **str, char *envp_path)
{
	if (**str == '\0')
		return (0);
	if (ft_strcmp(*str, ".") == 0)
		return (2);
	if (!is_path(*str))
		return (locate_and_replace(str, envp_path));
	return (file_status(*str));
}
