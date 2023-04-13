/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:37:19 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 19:25:02 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_path(char **env)
{
	char		*path;

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

char	*get_bin_path(char *cmd, char **path)
{
	char	*bin_path;
	int		i;
	DIR		*dir;

	dir = opendir(cmd);
	i = 0;
	bin_path = NULL;
	if (!access(cmd, X_OK) && !dir)
		return (free_tab(path, -1), free(dir), ft_strdup(cmd));
	else if (!dir && access(cmd, X_OK) == -1 && (!path || !*path))
		return (free_tab(path, -1), free(dir), NULL);
	if (!path)
		return (free_tab(path, -1), free(dir), NULL);
	while (path[i])
	{
		bin_path = ft_strjoin_path(path[i], cmd);
		if (!bin_path)
			return (free_tab(path, -1), g_g.exit_malloc = 1, free(dir), NULL);
		if (!access(bin_path, X_OK))
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	return (free_tab(path, -1), free(dir), bin_path);
}
