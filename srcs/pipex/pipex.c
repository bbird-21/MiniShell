/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/28 11:43:53 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static int counter(t_list *cmd)
{
    int		i;
    t_list *tmp;
	t_cmd	*content;

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


void	st_fill(t_storage_cmd *st_cmd, t_cmd *cmd)
{
	char	**arg;
	char	**path;

	arg = translator(cmd->arg, trans_token);
	st_cmd->ok = 1;
	st_cmd->fd_in = cmd->infile; /* if -2 : no infile */
	st_cmd->fd_out = cmd->outfile; /* if -2 : no outfile */
	if (cmd->pfd[1])
		st_cmd->toclose = cmd->pfd[1];
	else
		st_cmd->toclose = 0;
	st_cmd->bin_args = arg;
	if (arg)
		st_cmd->bin_path = get_bin_path(arg[0], get_path(st_cmd->env));
	else
	{
		st_cmd->bin_path = NULL;
		st_cmd->ok = 0;
	}
}

static void	st_init(t_list	*list, t_storage_cmd *st_cmd)
{
	st_cmd->nb_cmd = counter(list);
	st_cmd->fd_tmp = 0;
	st_cmd->pos = 0;
	st_cmd->pid = malloc(sizeof(int) * st_cmd->nb_cmd);
}

static void	fill_bin(t_list	*list, t_storage_cmd *st_cmd)
{
	t_cmd			*cmd;
	int				status;
	t_list			*lst;
	int 			i;
	
	i = -1;
	lst = list;
	st_init(list, st_cmd);
	signal(SIGQUIT, &sig_handler);
	mini_gc(list, NULL);
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
            	execve_builtin(is_builtin(st_cmd->bin_args[0], 0), st_cmd->bin_args);
				mini_gc(NULL, NULL);
				return ;
			}
		}
		loop_job(st_cmd);
		st_cmd->pos++;
		lst = lst->next;
		empty_data(st_cmd);
	}
	ft_lstclear(&list, cmd_cleaner);
	close(st_cmd->pfd[0]);
	if (st_cmd->fd_tmp)
		close(st_cmd->fd_tmp);
	if (st_cmd->toclose)
		close(st_cmd->toclose);
	while (++i < st_cmd->pos)
		waitpid(st_cmd->pid[i], &status, 0);
	clean_data(st_cmd);
	ft_out(&status);
}

void	pipex(t_list **cmd)
{
	t_storage_cmd	st_cmd;
	
	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	fill_bin(*cmd, &st_cmd);
}
