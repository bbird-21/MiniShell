/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:38:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/20 20:25:14 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnchr(char *s1, char *s2, size_t len)
{
	unsigned int	i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] || s2[i]) && --len)
		i++;
	if (s1[i] == s2[i])
		return (&s1[i]);
	return (NULL);
}

char	*ft_strjoin_path(char *line, char *buffer)
{
	char	*p;
	int		i;
	int		j;

	j = 0;
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen((char *)line)
				+ ft_strlen((char *)buffer)) + 3);
	if (!p)
		return (NULL);
	if (line != NULL)
	{
		while (line[i])
		{
			p[i] = line[i];
			i++;
		}
	}
	p[i] = '/';
	i++;
	while (buffer[j])
		p[i++] = buffer[j++];
	p[i] = '\0';
	return (p);
}

// void	close_fds(t_storage_cmd *st_cmd)
// {
// 	if (st_cmd->fd[0] != -1)
// 		close(st_cmd->fd[0]);
// 	if (st_cmd->fd[1] != -1)
// 		close(st_cmd->fd[1]);
// 	if (st_cmd->pfd[0] != -1)
// 		close(st_cmd->pfd[0]);
// 	if (st_cmd->pfd[1] != -1)
// 		close(st_cmd->pfd[1]);
// }

void	cmd_not_found(t_storage_cmd *node)
{
	ft_putstr_fd("command not found: ", STDOUT_FILENO);
	ft_putstr_fd(node->bin_args[0], STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	// lstfree(st_cmd);
	// close_fds(node);
	if (node->fd_in > 2)
		close(node->fd_in);
	exit(21);
}