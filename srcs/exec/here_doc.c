/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/30 14:10:02 by ale-sain         ###   ########.fr       */
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

static int	do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		// signal(SIGINT, &sigint); // a modifier
		free(line);
		if (g_exit_status == -1)
		{
			ft_lstclear(lst, cmd_cleaner);
			printf("here_doc\n");
			return (0);
		}
		line = readline("heredoc> ");
		if (!line)
		{
			nul_character(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, ((t_cmd *)((*lst)->content))->pfd[1]);
		if (!ft_strcmp(line, "\n"))
			ft_putstr_fd("\n", ((t_cmd *)((*lst)->content))->pfd[1]);
	}
	return (1);
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
	int		pid;

	tmp = (*list);
	cmd = (t_cmd *)(tmp->content);
	if (pipe(cmd->pfd) == -1)
		free_exit("pipe");
	pid = fork();
	if (pid < 0)
		free_exit("fork");
	if (pid == 0)
	{
		ft_state(3);
		signal(SIGINT, &sig_handler);
		while (tmp)
		{
			red = cmd->red;
			cmd = (t_cmd *)(tmp->content);
			while (red)
			{
				token = (t_token *)(red->content);
				if (token && token->type == DRIN)
				{
					if (!do_here_doc(&tmp, token->value))
					{
						g_exit_status = 0;
						printf("Test\n");
						return ;
					}
				}
				red = red->next;
			}
			tmp = tmp->next;
		}
		exit(21);
	}
	else
	{
		ft_state(4);
	}
	waitpid(pid, NULL, 0);
	return (opening(list));
}
