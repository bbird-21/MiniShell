/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 17:32:12 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/18 16:26:32 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	nul_character(char *limiter)
{
	ft_putstr_fd("\nwarning: here-document ", STDOUT_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted ", STDOUT_FILENO);
	ft_putstr_fd(limiter, STDOUT_FILENO);
	ft_putstr_fd(")\n", STDOUT_FILENO);
}

static void do_here_doc(t_list **lst, char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_strcmp(line, limiter))
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_lstclear(lst, token_cleaner) ,free_exit(NULL));
		if (!*line)
		{
			nul_character(limiter);
			break ;
		}
		if (ft_strcmp(line, limiter))
			break ;
		ft_putstr_fd(line, ((t_cmd *)((*lst)->content))->pfd[1]);
		if (!ft_strcmp(line, "\n"))
			ft_putstr_fd("\n", ((t_cmd *)((*lst)->content))->pfd[1]);
	}
	free(line);
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
			if (pipe(cmd->pfd) == -1)
				free_exit("pipe");
			token = (t_token *)(red->content);
			if (token && token->type == DRIN)
				do_here_doc(list, token->value);
			red = red->next;
		}
		tmp = tmp->next;
	}
	// close(cmd->pfd[1]);
	// read_pipe(*list);
	return (opening(list));
}
