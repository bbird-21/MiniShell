/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:56:40 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 14:05:25 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_out(int *status)
{
	if (WIFEXITED(*status))
		g_exit_status = WEXITSTATUS(*status);
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
	if (cmd)
		c = cmd;
	if (st)
		s = st;
}
