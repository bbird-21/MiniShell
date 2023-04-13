/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/13 19:44:32 by mmeguedm         ###   ########.fr       */
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

static int	do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		free(line);
		line = readline("heredoc> ");
		if (g_g.exit_here_doc)
			return (0);
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

static void	end_here_doc(int stdin_cpy, t_list **list)
{
	dup2(stdin_cpy, 0);
	close(stdin_cpy);
	if (g_g.exit_here_doc == 1)
	{
		g_g.exit_here_doc = 0;
		return (ft_lstclear(list, cmd_cleaner));
	}
	return (opening(list));
}

static void	init(int *stdin_cpy)
{
	*stdin_cpy = dup(0);
	ft_state(HERE_DOC);
	signal(SIGINT, &sig_handler);
}

void	here_doc(t_list **list, t_list *tmp, t_cmd *cmd)
{
	t_token	*token;
	t_list	*red;
	int		stdin_cpy;

	stdin_cpy = 0;
	tmp = (*list);
	init(&stdin_cpy);
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
	end_here_doc(stdin_cpy, list);
}
