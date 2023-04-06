/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:36:05 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/07 00:02:55 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_exe(t_storage_cmd *st_cmd, t_list *cmd)
{
	protecting(st_cmd, cmd);
	dupping(st_cmd);
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
	if (st_cmd->toclose)
		close(st_cmd->toclose);
	if (st_cmd->fd_tmp)
		close(st_cmd->fd_tmp);
	closing_cmd(cmd);
	if (is_builtin(st_cmd->bin_args[0], 1) != -1)
	{
		execve_builtin(is_builtin(st_cmd->bin_args[0], 1), st_cmd->bin_args);
		return (mini_gc(NULL, NULL));
	}
	else if (!st_cmd->bin_args || !st_cmd->bin_path)
		cmd_not_found(st_cmd, cmd);
	else if (execve(st_cmd->bin_path, st_cmd->bin_args, st_cmd->env) == -1)
		cmd_not_found(st_cmd, cmd);
	// g_exit_status = execve(st_cmd->bin_path, st_cmd->bin_args, st_cmd->env);
	// 	cmd_not_found(st_cmd, cmd);
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
		dup2(st_cmd->fd_tmp, STDIN_FILENO);
	if (st_cmd->fd_out >= 0)
	{
		dup2(st_cmd->fd_out, STDOUT_FILENO);
		if (st_cmd->fd_out > 2)
			close(st_cmd->fd_out);
	}
	else if (st_cmd->pos != st_cmd->nb_cmd - 1)
		dup2(st_cmd->pfd[1], STDOUT_FILENO);
}

void	protecting(t_storage_cmd *st_cmd, t_list *cmd)
{
	if (st_cmd->ok == 0 || st_cmd->fd_in == -1)
	{
		close(st_cmd->pfd[0]);
		close(st_cmd->pfd[1]);
		if (st_cmd->fd_in > 2)
			close(st_cmd->fd_in);
		if (st_cmd->fd_out > 2)
			close(st_cmd->fd_out);
		if (st_cmd->fd_tmp)
			close(st_cmd->fd_tmp);
		if (st_cmd->toclose)
			close(st_cmd->toclose);
		closing_cmd(cmd);
		mini_gc(NULL, NULL);
		handler(CLEANING, NULL, NULL);
		if (st_cmd->fd_in == -1)
			exit(1);
		exit(0);
	}
}

void	loop_job(t_storage_cmd *st_cmd, t_list *cmd)
{
	if (pipe(st_cmd->pfd) == -1)
		free_exit("pipe");
	st_cmd->pid[st_cmd->pos] = fork();
	if (st_cmd->pid[st_cmd->pos] == -1)
		free_exit("fork");
	else if (st_cmd->pid[st_cmd->pos] == 0)
	{
		ft_state(-1);
		dup_and_exe(st_cmd, cmd);
	}
	else
	{
		ft_state(PIPEX);
		if (st_cmd->pos != 0)
			close(st_cmd->fd_tmp);
		if (st_cmd->pos != st_cmd->nb_cmd - 1)
			st_cmd->fd_tmp = st_cmd->pfd[0];
		close(st_cmd->pfd[1]);
		if (st_cmd->fd_in > 2)
			close(st_cmd->fd_in);
		if (st_cmd->fd_out > 2)
			close(st_cmd->fd_out);
		if (st_cmd->toclose > 2)
			close(st_cmd->toclose);
	}
	// printf("fork : %d\n", st_cmd->pid[st_cmd->pos] = fork());
}
