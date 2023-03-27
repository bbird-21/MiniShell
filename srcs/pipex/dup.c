/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:36:05 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/27 19:01:03 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_exe(t_storage_cmd *st_cmd)
{
	dupping(st_cmd);
	protecting(st_cmd);
	if (st_cmd->toclose)
	{
		// printf("to close : %d\n", st_cmd->toclose);
		close(st_cmd->toclose);
	}
	if (is_builtin(st_cmd->bin_args[0], 1) != -1)
		execve_builtin(is_builtin(st_cmd->bin_args[0], 1), st_cmd->bin_args);
	else if (!st_cmd->bin_args || !st_cmd->bin_path)
		cmd_not_found(st_cmd);
	else if (execve(st_cmd->bin_path, st_cmd->bin_args, st_cmd->env) == -1)
		cmd_not_found(st_cmd);
}

void	dupping(t_storage_cmd *st_cmd)
{
	if (st_cmd->fd_in >= 0)
	{
		dup2(st_cmd->fd_in, STDIN_FILENO);
		if (st_cmd->fd_in > 2)
			close(st_cmd->fd_in);
	}
	else if (st_cmd->fd_tmp)
	{
		printf("dup_fd_tmp done\n");
		dup2(st_cmd->fd_tmp, STDIN_FILENO);
	}
	if (st_cmd->fd_out >= 0)
	{
		dup2(st_cmd->fd_out, STDOUT_FILENO);
		if (st_cmd->fd_out > 2)
			close(st_cmd->fd_out);
	}
	else if (st_cmd->pos != st_cmd->nb_cmd - 1)
	{
		// printf("st_cmd->pos : %d\tst_cmd->nb_cmd : %d\n", st_cmd->pos, st_cmd->nb_cmd);
		printf("dup_pfd[1] done\n");
		dup2(st_cmd->pfd[1], STDOUT_FILENO);
	}
}

void	protecting(t_storage_cmd *st_cmd)
{
	if (st_cmd->ok == 0 || st_cmd->fd_in == -1) /* if not any command or fdin or fdout invalid*/
		{
		if (st_cmd->toclose)
			close(st_cmd->toclose);
		mini_gc(NULL, NULL);
		handler(CLEANING, NULL, NULL);
		/*	Impossible  */
		if (st_cmd->fd_in == -1)
		{
			printf("test\n");
			exit(1);
		}
		exit(0);
	}
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
}

