/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 19:26:15 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/18 16:45:22 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**extra_bin_args(char *cmd, char *bin, int i)
// {
// 	char	**str;

// 	str = malloc(sizeof(char *) * 3);
// 	str[0] = ft_strdup(bin);
// 	str[1] = ft_strdup(&cmd[i]);
// 	str[2] = NULL;
// 	return (str);
// }

// void	extra_init(t_data *data)
// {
// 	if (data->fd[0] != -1)
// 		close(data->fd[0]);
// 	perror(data->args.argv[data->args.argc - 1]);
// 	// exit(EXIT_FAILURE);
// }

// void	extra_loop_free(t_storage_cmd *node)
// {
// 	int	i;

// 	i = -1;
// 	if (node->bin_args != NULL)
// 	{
// 		while (node->bin_args[++i])
// 			free(node->bin_args[i]);
// 	}
// 	free(node->bin_args);
// 	i = -1;
// 	if (node->path != NULL)
// 	{
// 		while (node->path[++i])
// 			free(node->path[i]);
// 	}
// 	free(node->path);
// }

// void	loop_job(t_storage_cmd *st_cmd)
// {
// 	if (pipe(st_cmd->pfd) == -1)
// 		free_exit("pipe");
// 	st_cmd->pid[st_cmd->pos] = fork();
// 	if (st_cmd->pid[st_cmd->pos] == -1)
// 		free_exit("fork");
// 	else if (st_cmd->pid[st_cmd->pos] == 0)
// 		dup_and_exe(st_cmd, st_cmd->bin_args);
// 	else
// 	{
// 		close(st_cmd->pfd[1]);
// 		if (st_cmd->pos != 0 )
// 			close(st_cmd->fd_tmp); /* ?? a echanger, modifier?*/
// 		if (st_cmd->pos != st_cmd->nb_cmd - 1)
// 			st_cmd->fd_tmp = st_cmd->pfd[0];
// 		// close(st_cmd->pfd[0]);
// 	}
// }
