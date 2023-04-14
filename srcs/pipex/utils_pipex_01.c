/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:38:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/14 23:36:05 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	counter(t_list *cmd)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = cmd;
	if (!tmp)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

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
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
	if (line != NULL)
	{
		while (line[i])
		{
			p[i] = line[i];
			i++;
		}
	}
	p[i++] = '/';
	while (buffer[j])
		p[i++] = buffer[j++];
	return (p[i] = '\0', p);
}

void	closing_cmd(t_list *cmd)
{
	t_list	*tmp;
	t_cmd	*data;

	tmp = cmd;
	while (tmp)
	{
		data = (t_cmd *)tmp->content;
		if (data->infile > 2)
			close(data->infile);
		if (data->outfile > 2)
			close(data->outfile);
		tmp = tmp->next;
	}
}

void	cmd_not_found(t_storage_cmd *node)
{
	ft_putstr_fd("command not found: ", STDERR_FILENO);
	ft_putstr_fd(node->bin_args[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (node->fd_in > 2)
		close(node->fd_in);
	if (node->fd_out > 2)
		close(node->fd_out);
	mini_gc(NULL, NULL);
	handler(CLEANING, NULL, NULL);
	exit(127);
}
