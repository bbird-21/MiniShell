/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/22 15:54:38 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	ft_close(int fd, char *str)
// {
// 	int a;

// 	printf("\t\t\t\t\t\tin %s -> fd %d : ", str, fd);
// 	a = close(fd);
// 	if (!a)
// 		printf("success\n");
// 	else
// 		printf("failure\n");
// }

void	loop_job(t_storage_cmd *st_cmd)
{
	if (pipe(st_cmd->pfd) == -1)
		free_exit("pipe");
	st_cmd->pid[st_cmd->pos] = fork();
	if (st_cmd->pid[st_cmd->pos] == -1)
		free_exit("fork");
	else if (st_cmd->pid[st_cmd->pos] == 0)
		dup_and_exe(st_cmd);
	else
	{
		if (st_cmd->pos != st_cmd->nb_cmd - 1)
			st_cmd->fd_tmp = st_cmd->pfd[0];
	}
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

void	protecting(t_storage_cmd *st_cmd)
{
	if (st_cmd->ok == 0 || st_cmd->fd_in == -1) /* if not any command or fdin or fdout invalid*/
	{
		close(st_cmd->pfd[0]);
		close(st_cmd->pfd[1]);
		if (st_cmd->toclose)
			close(st_cmd->toclose);
		if (st_cmd->fd_in == -1)
			exit(1);
		exit(0);
	}
}

void	dup_and_exe(t_storage_cmd *st_cmd)
{
	// printf("path : %s\n", st_cmd->bin_path);
	protecting(st_cmd);
	dupping(st_cmd);
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
	if (st_cmd->toclose)
			close(st_cmd->toclose);
	if (is_builtin(st_cmd->bin_args[0], 1) != -1)
		execve_builtin(is_builtin(st_cmd->bin_args[0], 1), st_cmd->bin_args);
	else
	{
		if (execve(st_cmd->bin_path, st_cmd->bin_args, st_cmd->env) == -1)
			cmd_not_found(st_cmd);
	}
}

void	fill_data_bin(t_storage_cmd *st_cmd, t_cmd *cmd)
{
	char	**arg;

	arg = translator(cmd->arg, trans_token);
	st_cmd->ok = 1;
	st_cmd->fd_in = cmd->infile; /* if -2 : no infile */
	st_cmd->fd_out = cmd->outfile; /* if -2 : no outfile */
	st_cmd->bin_args = arg;
	if (arg)
		st_cmd->bin_path = get_bin_path(arg[0], get_path(st_cmd->env));
	else
	{
		st_cmd->bin_path = NULL;
		st_cmd->ok = 0;
	}
}

int	ft_out(int *status)
{
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else
		return (0);
}

static void	fill_bin(t_list	*list, t_storage_cmd *st_cmd)
{
	t_cmd			*cmd;
	int				status;

	st_cmd->nb_cmd = counter(list);
	st_cmd->fd_tmp = 0;
	st_cmd->pos = 0;
	st_cmd->pid = malloc(sizeof(int) * st_cmd->nb_cmd);
	cmd = (t_cmd *)list->content;
	if (cmd->pfd[1])
		st_cmd->toclose = cmd->pfd[1];
	else
		st_cmd->toclose = 0;
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		fill_data_bin(st_cmd, cmd);
		if (st_cmd->nb_cmd == 1 && st_cmd->bin_args)
   		{
        	if (is_builtin(st_cmd->bin_args[0], 0) != -1 && st_cmd->fd_in != -1)
        	{
            	execve_builtin(is_builtin(st_cmd->bin_args[0], 0), st_cmd->bin_args);
				return ;
			}
		}
		loop_job(st_cmd);
		close(st_cmd->pfd[1]);
		st_cmd->pos++;
		list = list->next;
	}
	close(st_cmd->pfd[0]);
	if (st_cmd->fd_tmp)
		close(st_cmd->fd_tmp);
	if (st_cmd->toclose)
			close(st_cmd->toclose);
	int i = 0;
	while (i < st_cmd->pos)
	{
		// printf("st_cmd[%d] : %d\n", i, st_cmd->pid[i]);
		waitpid(st_cmd->pid[i], &status, 0);
		i++;
	}
	g_exit_status = ft_out(&status);
}

void	pipex(t_list **cmd)
{
	t_storage_cmd	st_cmd;
	
	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	fill_bin(*cmd, &st_cmd);
}
