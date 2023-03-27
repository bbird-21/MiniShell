/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/27 19:06:14 by mmeguedm         ###   ########.fr       */
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



void	fill_data_bin(t_storage_cmd *st_cmd, t_cmd *cmd)
{
	char	**arg;
	char	**path;

	arg = translator(cmd->arg, trans_token);
	st_cmd->ok = 1;
	st_cmd->fd_in = cmd->infile; /* if -2 : no infile */
	// printf("cmd fd_in = %d\n", st_cmd->fd_in);
	st_cmd->fd_out = cmd->outfile; /* if -2 : no outfile */
	// printf("cmd fd_out = %d\n", st_cmd->fd_out);
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


void	loop_job(t_storage_cmd *st_cmd)
{
	if (pipe(st_cmd->pfd) == -1)
		free_exit("pipe");
	st_cmd->pid[st_cmd->pos] = fork();
	if (st_cmd->pid[st_cmd->pos] == -1)
		free_exit("fork");
	else if (st_cmd->pid[st_cmd->pos] == 0)
	{
		ft_state(2);
		dup_and_exe(st_cmd);
	}
	else
	{
		ft_state(1);
		close(st_cmd->pfd[1]);
		if (st_cmd->pos != 0)
			close(st_cmd->fd_tmp);
		if (st_cmd->pos != st_cmd->nb_cmd - 1)
			st_cmd->fd_tmp = st_cmd->pfd[0];
	}
}

static void	fill_bin(t_list	*list, t_storage_cmd *st_cmd)
{
	t_cmd			*cmd;
	int				status;
	t_list			*lst;
	int 			i;
	
	i = -1;
	lst = list;
	st_cmd->nb_cmd = counter(list);
	st_cmd->fd_tmp = 0;
	st_cmd->pos = 0;
	st_cmd->pid = malloc(sizeof(int) * st_cmd->nb_cmd);
	cmd = (t_cmd *)list->content; 
	signal(SIGQUIT, &sig_handler);
	mini_gc(list, NULL);
	while (lst)
	{
		ft_state(1);
		cmd = (t_cmd *)(lst->content);
		fill_data_bin(st_cmd, cmd);
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
		if (st_cmd->fd_in > 2)
			close(st_cmd->fd_in);
		if (st_cmd->fd_out > 2)
			close(st_cmd->fd_out);
		if (st_cmd->toclose > 2)
			close(st_cmd->toclose);
		st_cmd->pos++;
		printf("st_cmd->pos : %d\n", st_cmd->pos);
		lst = lst->next;
		empty_data(st_cmd);
	}
	ft_lstclear(&list, cmd_cleaner);
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
	if (st_cmd->fd_tmp)
		close(st_cmd->fd_tmp);
	if (st_cmd->toclose)
		close(st_cmd->toclose);
	while (++i < st_cmd->pos)
	{
		printf("pid : %d\n", st_cmd->pid[i]);
		waitpid(st_cmd->pid[i], &status, 0);
	}
	clean_data(st_cmd);
	ft_out(&status);
}

void	pipex(t_list **cmd)
{
	t_storage_cmd	st_cmd;
	
	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	fill_bin(*cmd, &st_cmd);
}
