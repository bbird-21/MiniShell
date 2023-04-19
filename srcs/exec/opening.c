/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:21:25 by alvina            #+#    #+#             */
/*   Updated: 2023/04/19 18:31:20 by mmeguedm         ###   ########.fr       */
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
		if (old_fd > 2)
			close(old_fd);
		fd = open(token->value, O_RDONLY);
		if (fd == 0 || fd == -1)
		{
			if (cmd->outfile > 2)
				close(cmd->outfile);
			cmd->infile = -1;
			cmd->outfile = -1;
			return (perror(token->value), 0);
		}
		cmd->infile = fd;
	}
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

static void	exploring_red(t_list *red, t_cmd *content)
{
	t_token	*data;

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
}

void	opening(t_list **cmd)
{
	t_cmd	*content;
	t_list	*red;
	t_list	*lst;

	lst = *cmd;
	while (lst)
	{
		content = (t_cmd *)lst->content;
		red = content->red;
		exploring_red(red, content);
		lst = lst->next;
	}
	return (pre_pipex(cmd));
}
