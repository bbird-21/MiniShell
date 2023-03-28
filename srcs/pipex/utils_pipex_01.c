/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 02:38:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/28 13:09:03 by ale-sain         ###   ########.fr       */
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

void	closing_cmd(t_list *cmd)
{
	t_list *tmp;
	t_cmd *data;

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

void	cmd_not_found(t_storage_cmd *node, t_list *cmd)
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

