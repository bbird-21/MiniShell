/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 19:37:19 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 13:52:25 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_bin_path(char *cmd, char **path)
{
	char	*bin_path;
	int		i;

	i = 0;
	bin_path = NULL;
	if (!access(cmd, X_OK))
	{
		if (path)
			free_tab(path, -1);
		return (ft_strdup(cmd));
	}
	else if (access(cmd, X_OK) == -1 && (!path || !*path))
		return (NULL);
	while (path[i])
	{
		bin_path = ft_strjoin_path(path[i], cmd);
		if (!bin_path)
			return (free_exit("memory_error"), NULL);
		if (!access(bin_path, X_OK))
			break ;
		free(bin_path);
		bin_path = NULL;
		i++;
	}
	return (free_tab(path, -1), bin_path);
}
