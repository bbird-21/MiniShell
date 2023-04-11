/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/11 15:58:22 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	st_fill(t_storage_cmd *st_cmd, t_cmd *cmd)
{
	char	**arg;
	char	**path;

	arg = translator(cmd->arg, trans_token);
	if (!arg && g.exit_malloc == 1)
	{
		mini_gc(NULL, NULL);
		clean_data(st_cmd);
		exit_malloc();
	}
	st_cmd->ok = 1;
	st_cmd->fd_in = cmd->infile;
	st_cmd->fd_out = cmd->outfile;
	if (cmd->pfd[1])
		st_cmd->toclose = cmd->pfd[1];
	else
		st_cmd->toclose = 0;
	st_cmd->bin_args = arg;
	int i = 0;
	while (arg[i])
		printf("%s \n", arg[i++]);
	if (arg)
		st_cmd->bin_path = get_bin_path(arg[0], get_path(st_cmd->env));
	else
	{
		st_cmd->bin_path = NULL;
		st_cmd->ok = 0;
	}
	if (st_cmd->bin_path == NULL && g.exit_malloc == 1)
	{
		mini_gc(NULL, NULL);
		clean_data(st_cmd);
		exit_malloc();
	}
}

static void	st_init(t_list *list, t_storage_cmd *st_cmd)
{
	st_cmd->nb_cmd = counter(list);
	st_cmd->fd_tmp = 0;
	st_cmd->pos = 0;
	st_cmd->pid = malloc(sizeof(int) * st_cmd->nb_cmd);
}

static void	post_pipex(t_storage_cmd *st_cmd, t_list *list)
{
	int	status;
	int	i;

	i = -1;
	ft_lstclear(&list, cmd_cleaner);
	close(st_cmd->pfd[0]);
	if (st_cmd->fd_tmp)
		close(st_cmd->fd_tmp);
	if (st_cmd->toclose)
		close(st_cmd->toclose);
	while (++i < st_cmd->pos)
	{
		waitpid(st_cmd->pid[i], &status, 0);
		if (status == -21)
		{
			mini_gc(NULL, NULL);
			exit_malloc();
		}
	}
	clean_data(st_cmd);
	ft_out(&status);
}

static void	pipex(t_list *list, t_storage_cmd *st_cmd)
{
	t_cmd	*cmd;
	t_list	*lst;

	lst = list;
	while (lst)
	{
		ft_state(1);
		cmd = (t_cmd *)(lst->content);
		st_fill(st_cmd, cmd);
		mini_gc(NULL, st_cmd);
		if (st_cmd->nb_cmd == 1 && st_cmd->bin_args)
		{
			if (is_builtin(st_cmd->bin_args[0], 0) != -1 && st_cmd->fd_in != -1)
			{
				execve_builtin(is_builtin(st_cmd->bin_args[0], 0),
					st_cmd->bin_args);
				if (g.exit_malloc == 1)
				{
					mini_gc(NULL, NULL);
					exit_malloc();
				}
				return (mini_gc(NULL, NULL));
			}
		}
		loop_job(st_cmd, lst);
		st_cmd->pos++;
		lst = lst->next;
		empty_data(st_cmd);
	}
	post_pipex(st_cmd, list);
}

void	pre_pipex(t_list **cmd)
{
	t_storage_cmd	st_cmd;

	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	if (!st_cmd.env)
	{
		ft_lstclear(cmd, cmd_cleaner);
		exit_malloc();
	}
	st_init(*cmd, &st_cmd);
	if (!st_cmd.pid)
	{
		free_tab(st_cmd.env, -1);
		ft_lstclear(cmd, cmd_cleaner);
		exit_malloc();
	}
	signal(SIGQUIT, &sig_handler);
	mini_gc(*cmd, NULL);
	pipex(*cmd, &st_cmd);
}
