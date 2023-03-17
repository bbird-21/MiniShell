/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:47:51 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/17 20:18:48 by alvina           ###   ########.fr       */
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
		// content = (t_cmd *)tmp->content;
        // if (content->infile != -1 && content->arg)
			i++;
		tmp = tmp->next;
    }
    return (i);
}

// void	init_list(t_data *data)
// {
// 	data->dblist.first = NULL;
// 	data->dblist.last = NULL;
// }

// if (st_cmd->pos == 1)
	// {
	// 	if (st_cmd->fd[0] == -1)
	// 	{
	// 		dup2(st_cmd->pfd[1], STDOUT_FILENO);
	// 		return (free_exit("dup"));
	// 	}
	// 	else if (!ft_strcmp(data->args.argv[1], "here_doc"))
	// 		dup2(st_cmd->fd[0], STDIN_FILENO);
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

void	dup_and_exe(t_storage_cmd *st_cmd, char **cmd_args)
{
	if (st_cmd->ok == 1 || st_cmd->fd_in == -1) /* if not any command or fdin or fdout invalid*/
		exit(21);
	if (!st_cmd->bin_path || !st_cmd->bin_args)
		cmd_not_found(st_cmd);
	if (st_cmd->fd_tmp)
		dup2(st_cmd->fd_tmp, STDIN_FILENO);
	if (st_cmd->pos != st_cmd->nb_cmd - 1)
		dup2(st_cmd->pfd[1], STDOUT_FILENO);
	// close_fds(st_cmd);
	close(st_cmd->pfd[0]);
	close(st_cmd->pfd[1]);
	if (!st_cmd->bin_path || !st_cmd->bin_args)
		cmd_not_found(st_cmd);
	execve(st_cmd->bin_path, cmd_args, st_cmd->env);
	printf("error\n");
	// return (free_exit(st_cmd->bin));
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

static void	fill_bin(t_list	*list, t_storage_cmd *st_cmd)
{
	t_cmd			*cmd;

	st_cmd->nb_cmd = counter(list);
	st_cmd->fd_tmp = 0;
	st_cmd->pos = 0;
	st_cmd->pid = malloc(sizeof(int) * st_cmd->nb_cmd);
	while (list)
	{
		cmd = (t_cmd *)(list->content);
		// if (cmd->infile != -1 && cmd->arg)
		// {
			fill_data_bin(st_cmd, cmd);
			printf("nb : %d pos : %d\n", st_cmd->nb_cmd, st_cmd->pos);
			loop_job(st_cmd);
			st_cmd->pos++;
		// }
		list = list->next;
	}
	while (--st_cmd->pos >= 0)
	{
		printf("st_cmd[%d] : %d\n", st_cmd->pos, st_cmd->pid[st_cmd->pos]);
		waitpid(st_cmd->pid[st_cmd->pos], NULL, 0);
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
	// t_list			*tmp;
	// t_cmd			*cmd2;
	
	st_cmd.env = translator(handler(5, NULL, NULL), trans_env);
	printf("PIPEX !\n");
	fill_bin(*cmd, &st_cmd);
	// tmp = *cmd;
	// while (tmp)
	// {
	// 	printf(":)\n");
	// 	cmd2 = (t_cmd *)(tmp->content);
	// 	while (cmd2->arg)
	// 	{
	// 		printf("arg->value : %s\n", ((t_token *)(cmd2->arg->content))->value);
	// 		printf("infile = %d\n", cmd2->infile);
	// 		cmd2->arg = cmd2->arg->next;
	// 	}
	// 	tmp = tmp->next;
	// }



	// init_list(&data);
	// fill_bin(argc, argv, env, &data);
	// launcher(&data);
	// close_fds(&data);
	// lstfree(&data);
}
