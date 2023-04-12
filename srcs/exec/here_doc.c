/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/12 19:50:31 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

static void	nul_character(char *limiter)
{
	ft_putstr_fd("warning: here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted ", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd(")\n", STDOUT_FILENO);
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

static void	exit_here_doc()
{
	g.exit_here_doc = 0;
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
	ft_state(HERE_DOC);
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
	close(stdin_cpy);
	if (g.exit_here_doc == 1)
		return (exit_here_doc());
	return (opening(list));
}
