/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:26:15 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/16 17:24:00 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extra_bin_args(char *cmd, char *bin, int i)
{
	char	**str;

	str = malloc(sizeof(char *) * 3);
	str[0] = ft_strdup(bin);
	str[1] = ft_strdup(&cmd[i]);
	str[2] = NULL;
	return (str);
}

void	extra_init(t_data *data)
{
	if (data->fd[0] != -1)
		close(data->fd[0]);
	perror(data->args.argv[data->args.argc - 1]);
	// exit(EXIT_FAILURE);
}

void	extra_loop_free(t_storage_cmd *node)
{
	int	i;

	i = -1;
	if (node->bin_args != NULL)
	{
		while (node->bin_args[++i])
			free(node->bin_args[i]);
	}
	free(node->bin_args);
	i = -1;
	if (node->path != NULL)
	{
		while (node->path[++i])
			free(node->path[i]);
	}
	free(node->path);
}

void	loop_job(t_storage_cmd *st_cmd, int i, char **cmd_arg)
{
	if (pipe(st_cmd->pfd) == -1)
		free_exit("pipe");
	st_cmd->pid[i] = fork();
	if (st_cmd->pid[i] == -1)
		free_exit("fork");
	else if (st_cmd->pid[i] == 0)
		dup_and_exe(st_cmd, cmd_arg);
	else
	{
		close(st_cmd->pfd[1]);
		st_cmd->fd_in = st_cmd->pfd[0];
		// if (i != 0)
			// close(st_cmd->fd_in);
		// if (i != st_cmd->nb_cmd)
	}
}
