/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:40 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 19:38:50 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_pipex_malloc(t_storage_cmd *st_cmd)
{
	mini_gc(NULL, NULL);
	clean_data(st_cmd);
	exit_malloc();
}

void	ft_out(int *status)
{
	if (WIFEXITED(*status))
		g_g.exit_status = WEXITSTATUS(*status);
}

void	empty_data(t_storage_cmd *cmd)
{
	if (cmd->bin_args)
		free_tab(cmd->bin_args, -1);
	if (cmd->bin_path)
		free(cmd->bin_path);
}

void	clean_data(t_storage_cmd *cmd)
{
	if (cmd->env)
		free_tab(cmd->env, -1);
	if (cmd->pid)
		free(cmd->pid);
}

void	mini_gc(t_list *cmd, t_storage_cmd *st)
{
	static t_list			*c;
	static t_storage_cmd	*s;

	if (!cmd && !st)
	{
		if (c)
		{
			ft_lstclear(&c, cmd_cleaner);
			c = NULL;
		}
		if (s)
		{
			empty_data(s);
			clean_data(s);
			s = NULL;
		}
		return ;
	}
	else
	{
		if (cmd)
			c = cmd;
		if (st)
			s = st;
	}
}
