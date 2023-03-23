/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/22 18:01:43 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

void	nul_character(char *limiter)
{
	ft_putstr_fd("warning: here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted ", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd(")\n", STDOUT_FILENO);
}

void	sigint(int signum)
{
		g_exit_status = -1;
}

static void do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		signal(SIGINT, &sigint); // a modifier
		if (g_exit_status == -1)
		{
			g_exit_status = 130;
			ft_lstclear(lst, cmd_cleaner);
			return;
		}
		line = readline("heredoc> ");
		if (!line)
		{
			nul_character(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter))
			break ;
		ft_putstr_fd(line, ((t_cmd *)((*lst)->content))->pfd[1]);
		if (!ft_strcmp(line, "\n"))
			ft_putstr_fd("\n", ((t_cmd *)((*lst)->content))->pfd[1]);
		free(line);
	}
}

// void	read_pipe(t_list *list)
// {
// 	t_cmd	*cmd;
// 	char	msg[120];
// 	int		readed;

// 	printf("READ_PIPE\n");
// 	while (list)
// 	{
// 		printf("test\n");
// 		cmd = (t_cmd *)(list->content);
// 		while (cmd->red)
// 		{
// 			close(cmd->pfd[1]);
// 			readed = read(cmd->pfd[0], msg, 11);
// 			msg[readed] = 0;
// 			printf("msg : %s\n", msg);
// 			cmd->red = cmd->red->next;
// 		}
// 		list = list->next;
// 	}
// }

void	here_doc(t_list **list) 
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_token	*token;
	t_list	*red;

	tmp = (*list);
	while (tmp)
	{
		cmd = (t_cmd *)(tmp->content);
		red = cmd->red;
		while (red)
		{
			// printf("pipe : %d\n", cmd->pfd[1]);
			token = (t_token *)(red->content);
			if (token && token->type == DRIN)
			{
				if (pipe(cmd->pfd) == -1)
					free_exit("pipe");
				do_here_doc(list, token->value);
				if (g_exit_status == -1)
				{
					ft_putstr_fd("\n", 1);
					rl_on_new_line();
					g_exit_status = 130;
					return ;
				}
			}
			red = red->next;
		}
		tmp = tmp->next;
	}
	// read_pipe(*list);
	return (opening(list));
}
