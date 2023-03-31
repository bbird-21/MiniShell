/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/31 13:18:36 by ale-sain         ###   ########.fr       */
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
		g.exit_status = -1;
}

static int do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		free(line);
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


void	here_doc(t_list **list) 
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_token	*token;
	t_list	*red;
	int 	stdin_cpy;
	
	stdin_cpy = dup(0);
	tmp = (*list);
	ft_state(3);
	signal(SIGINT, &sig_handler);
	while (tmp)
	{
		cmd = (t_cmd *)(tmp->content);
		red = cmd->red;
		while (red)
		{
			token = (t_token *)(red->content);
			if (token && token->type == DRIN)
			{
				if (pipe(cmd->pfd) == -1)
					free_exit("pipe");
				do_here_doc(&tmp, token->value);
			}
			red = red->next;
		}
		tmp = tmp->next;
	}
	dup2(stdin_cpy, 0);
	return (opening(list));
}

// void	here_doc(t_list **list) 
// {
// 	t_list	*tmp;
// 	t_cmd	*cmd;
// 	t_token	*token;
// 	t_list	*red;
// 	int		pid;
// 	int		status;
// 	t_list	**test;
// 	int		tab[2];
	
// 	test = &tmp;
// 	printf("Hey\n");
// 	tmp = (*list);
// 	ft_state(3);
// 	// signal(SIGINT, &sig_handler);
// 	cmd = (t_cmd *)(tmp->content);
// 	while (tmp)
// 	{
// 		red = cmd->red;
// 		cmd = (t_cmd *)(tmp->content);
// 		while (red)
// 		{
// 			cmd = (t_cmd *)(tmp->content);
// 			token = (t_token *)(red->content);
// 			if (token && token->type == DRIN)
// 			{
// 				if (pipe(cmd->pfd) == -1)
// 					free_exit("pipe");
// 				// tab = cmd->pfd;
// 				// get_pfd(tab);
// 				do_here_doc(&tmp, token->value);
// 			}
// 			red = red->next;
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("size_list : %d\n", get_nb_cmd((*list)));
// 	printf("size_test : %d\n", get_nb_cmd(*test));
// 	return (opening(list));
// }


// void	here_doc(t_list **list) 
// {
// 	t_list	*tmp;
// 	t_cmd	*cmd;
// 	t_token	*token;
// 	t_list	*red;
// 	int		pid;
// 	int		status;

// 	printf("Hey\n");
// 	tmp = (*list);
// 	cmd = (t_cmd *)(tmp->content);
// 	if (pipe(cmd->pfd) == -1)
// 		free_exit("pipe");
// 	pid = fork();
// 	if (pid < 0)
// 		free_exit("fork");
// 	if (pid == 0)
// 	{
// 		ft_state(3);
// 		signal(SIGINT, &sig_handler);
// 		while (tmp)
// 		{
// 			red = cmd->red;
// 			cmd = (t_cmd *)(tmp->content);
// 			while (red)
// 			{
// 				token = (t_token *)(red->content);
// 				if (token && token->type == DRIN)
// 					do_here_doc(&tmp, token->value);
// 				red = red->next;
// 			}
// 			tmp = tmp->next;
// 		}
// 		if (g_exit_status == -1)
// 			exit(21);
// 		exit(42);
// 	}
// 	ft_state(4);
// 	waitpid(pid, &status, 0);
// 	if (WEXITSTATUS(status) == 21)
// 		return ;
// 	return (opening(list));
// }

