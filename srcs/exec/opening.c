/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:21:25 by alvina            #+#    #+#             */
/*   Updated: 2023/03/30 14:17:32 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	infiling(t_cmd *cmd, t_token *token)
{
	int	fd;
	int	old_fd;

	old_fd = cmd->infile;
	if (token->type == DRIN)
		cmd->infile = cmd->pfd[0];
	else
	{
		fd = open(token->value, O_RDONLY);
		if (fd == 0 || fd == -1)
		{
			if (cmd->outfile > 2)
				close(cmd->outfile);
			if (old_fd > 2)
				close(old_fd);
			cmd->infile = -1;
			cmd->outfile = -1;
			return (perror(token->value), 0);
		}
		cmd->infile = fd;
	}
	if (old_fd > 2)
		close(old_fd);
	return (1);
}

static int	outfiling(t_cmd *cmd, t_token *token)
{
	int	fd;
	int	old_fd;

	old_fd = cmd->outfile;
	if (token->type == ROUT)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (old_fd > 2)
		close(old_fd);
	if (fd == -1)
	{
		if (cmd->infile > 2)
			close(cmd->infile);
		cmd->infile = -1;
		cmd->outfile = -1;
		return (perror(token->value), 0);
	}
	cmd->outfile = fd;
	return (1);
}

// static void	print_files(t_list *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("\n-------------------\n");
// 		printf("infile : %d, outfile : %d\n", ((t_cmd *)(cmd->content))->infile,
				// ((t_cmd *)(cmd->content))->outfile);
// 		cmd = cmd->next;
// 	}
// }

void	opening(t_list **cmd)
{
	t_cmd	*content;
	t_list	*red;
	t_token	*data;
	t_list	*lst;

	lst = *cmd;
	while (lst)
	{
		content = (t_cmd *)lst->content;
		red = content->red;
		while (red)
		{
			data = (t_token *)red->content;
			if (data->type == RIN || data->type == DRIN)
			{
				if (!infiling(content, data))
					break ;
			}
			else
			{
				if (!outfiling(content, data))
					break ;
			}
			red = red->next;
		}
		lst = lst->next;
	}
	return (pre_pipex(cmd));
}
