/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/16 03:31:57 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_list(t_data *data)
{
	data->dblist.first = NULL;
	data->dblist.last = NULL;
}

void	dup_and_exe(t_storage_cmd *st_cmd, char **cmd_args)
{
	static int i;
	if (!st_cmd->bin_path || !cmd_args)
		cmd_not_found(st_cmd);
	// if (st_cmd->pos == 1)
	// {
	// 	if (st_cmd->fd[0] == -1)
	// 	{
	// 		dup2(st_cmd->pfd[1], STDOUT_FILENO);
	// 		return (free_exit("dup"));
		// }
		// else if (!ft_strcmp(data->args.argv[1], "here_doc"))
		// 	dup2(st_cmd->fd[0], STDIN_FILENO);
	// }
	// else
	// 	dup2(st_cmd->fd_in, STDIN_FILENO);
	// if (st_cmd->pos != st_cmd->nb_cmd)
	// else
	// {
	// 	if (dup2(st_cmd->fd[1], STDOUT_FILENO) == -1)
	// 		return (free_exit("dup"));
	// }
	// printf("test\n");
	// close_fds(st_cmd);
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
	execve(st_cmd->bin_path, cmd_args, st_cmd->env);
	printf("error\n");
	return (free_exit(st_cmd->bin));
}

void	fill_data_bin(t_storage_cmd *st_cmd, char *cmd)
{
	
	st_cmd->bin = get_bin(cmd);
	st_cmd->path = get_path(st_cmd->env);
	st_cmd->bin_args = get_bin_args(cmd, st_cmd->bin);
	st_cmd->bin_path = get_bin_path(cmd, st_cmd->bin, st_cmd->path);
}

static void	fill_bin(t_list	*list, t_storage_cmd *st_cmd)
{
	t_cmd			*cmd;
	t_token			*token;
	t_list			*cmd_list;
	char			**cmd_arg;
	int				i;

	i = 0;
	cmd = (t_cmd *)(list->content);
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		cmd_list = cmd->arg;
		token = (t_token *)(cmd_list->content);
		cmd_arg = translator(cmd->arg, trans_token);
		fill_data_bin(st_cmd, token->value);
		loop_job(st_cmd, i, cmd_arg);
		printf("i : %d\n", i);
		i++;
		list = list->next;
	}
	while (--i >= 0)
	{
		printf("st_cmd[%d] : %d\n", i, st_cmd->pid[i]);
		waitpid(st_cmd->pid[i], NULL, 0);
	}
	// while (first)
	// {
	// 	cmd = (t_cmd *)(first->content);
	// 	cmd_list = cmd->arg;
	// 	while (cmd_list)
	// 	{
	// 		token = (t_token *)(cmd_list->content);
	// 		printf("token->value     : %s\n", token->value);
	// 		printf("token->bin 		 : %s\n", token->bin);
	// 		printf("token->bin_path  : %s\n", token->bin_path);
	// 		cmd_list = cmd_list->next;
	// 	}
	// 	printf("next\n");
	// 	first = first->next;
	// }
	// while (actual_bin < argc - 1)
	// {
	// 	actual_bin++;
	// }
}

void	pipex(t_list **cmd)
{
	t_storage_cmd	st_cmd;
	
	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	printf("PIPEX !\n");
	// while (tmp)
	// {
	// 	cmd2 = (t_cmd *)(tmp->content);
	// 	arg = cmd2->arg;
	// 	while (arg)
	// 	{
	// 		token = (t_token *)(arg->content);
	// 		printf("arg->value : %s\n", token->value);
	// 		arg = arg->next;
	// 	}
	// 	tmp = tmp->next;
	// }
	fill_bin(*cmd, &st_cmd);
	// init_list(&data);
	// fill_bin(argc, argv, env, &data);
	// launcher(&data);
	// close_fds(&data);
	// lstfree(&data);
}
