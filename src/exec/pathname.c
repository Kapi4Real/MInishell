/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccouton <ccouton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 00:00:00 by ccouton           #+#    #+#             */
/*   Updated: 2025/06/29 00:00:00 by ccouton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_string	setup_t_string(char *str)
{
	t_string	string;

	string.ptr = str;
	if (!str)
		string.size = -1;
	else
		string.size = ft_strlen(str) + 1;
	return (string);
}

static int	create_pathname(t_string *pathname, t_string *exec, char *envp_path)
{
	int	path_len;
	int	add_slash;

	path_len = 0;
	while (envp_path[path_len] && envp_path[path_len] != ':')
		path_len++;
	add_slash = (path_len != 0 && envp_path[path_len - 1] != '/');
	if (path_len + add_slash + exec->size > pathname->size)
	{
		free(pathname->ptr);
		pathname->ptr = malloc((path_len + add_slash + exec->size)
				* sizeof (char));
		if (!pathname->ptr)
		{
			perror("malloc");
			return (-1);
		}
		pathname->size = path_len + add_slash + exec->size;
	}
	ft_strlcpy(pathname->ptr, envp_path, path_len + 1);
	if (add_slash)
		pathname->ptr[path_len] = '/';
	ft_strlcpy(pathname->ptr + path_len + add_slash, exec->ptr, exec->size);
	return (path_len);
}

static int	init_pathname(t_string *pathname, t_string *exec, char *exec_name)
{
	*exec = setup_t_string(exec_name);
	pathname->ptr = ft_strdup(exec_name);
	if (!pathname->ptr)
		return (-1);
	*pathname = setup_t_string(pathname->ptr);
	return (0);
}

static int	look_through_envp(char **name, char *envp_path)
{
	t_string	pathname;
	t_string	exec_name;
	int			jump;

	if (init_pathname(&pathname, &exec_name, *name) == -1)
		return (1);
	while (*envp_path)
	{
		envp_path += str_skip_char(envp_path, ':');
		jump = create_pathname(&pathname, &exec_name, envp_path);
		if (jump == -1)
			return (1);
		if (access(pathname.ptr, X_OK) == 0)
			if (!is_dir(pathname.ptr, 0))
				break ;
		envp_path += jump;
	}
	if (!*envp_path)
	{
		free(pathname.ptr);
		return (1);
	}
	free(*name);
	*name = pathname.ptr;
	return (0);
}

int	locate_and_replace(char **name, char *envp_path)
{
	int		err;
	char	*str_err;

	if (!envp_path)
	{
		if (access(*name, X_OK) != 0)
		{
			err = errno;
			str_err = strerror(err);
			str_error_message(*name, str_err);
			return (126 + (err == EACCES || err == ENOENT || err == ENOTDIR));
		}
		return (0);
	}
	if (look_through_envp(name, envp_path))
	{
		str_error_message(*name, "command not found");
		return (127);
	}
	return (0);
}
