/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:37:19 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/16 02:39:55 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bin(char *cmd)
{
	char	*bin;
	int		len;

	len = 0;
	while (cmd[len] && cmd[len] != ' ')
		len++;
	bin = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		free_exit("memory_error");
	len = 0;
	while (cmd[len] && cmd[len] != ' ')
	{
		bin[len] = cmd[len];
		len++;
	}
	bin[len] = '\0';
	return (bin);
}

char	**get_path(char **env)
{
	char	*path;

	if (!env || !*env)
		return (NULL);
	path = ft_strnchr(*env, "PATH", 5);
	while (*env && !path)
	{
		path = ft_strnchr(*env, "PATH=/", 6);
		env++;
	}
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

char	*get_bin_path(char *cmd, char *bin, char **path)
{
	char	*bin_path;
	int		i;

	i = 0;
	bin_path = NULL;
	if (!access(cmd, X_OK))
		return (ft_strdup(bin));
	else if (access(cmd, X_OK) == -1 && (!path || !*path))
		return (NULL);
	while (path[i])
	{
		bin_path = ft_strjoin_path(path[i], bin);
		if (!bin_path)
			return (free_exit("memory_error"), NULL);
		if (!access(bin_path, X_OK))
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	if (!bin_path)
		return (NULL);
	return (bin_path);
}

char	**get_bin_args(char *cmd, char *bin)
{
	char	**bin_args;
	int		i;

	i = 0;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
	{
		bin_args = malloc(sizeof(char *) * 2);
		bin_args[0] = ft_strdup(bin);
		bin_args[1] = NULL;
	}
	else if (cmd[i] == '-')
		bin_args = ft_split(cmd, ' ');
	else
		bin_args = extra_bin_args(cmd, bin, i);
	return (bin_args);
}
