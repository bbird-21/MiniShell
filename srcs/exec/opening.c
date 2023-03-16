/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:21:25 by alvina            #+#    #+#             */
/*   Updated: 2023/03/14 18:24:02 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	
static int	infiling(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (token->type == DRIN)
		cmd->infile = cmd->pfd[0];
	else
	{
		fd = open(token->value, O_RDONLY);
		if (fd == 0 || fd == -1)
			return (perror(token->value), 0);
		cmd->infile = fd;
	}
	printf("in : %d\n", cmd->infile);
	return (1);
}

static int outfiling(t_cmd *cmd, t_token *token)
{
	int	fd;

	if (token->type == ROUT)
		fd = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(token->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror(token->value), 0);
	cmd->outfile = fd;
	printf("out : %d\n", cmd->outfile);
	return (1);
}

static void	print_files(t_list *cmd)
{
	while (cmd)
	{
		printf("\n-------------------\n");
		printf("infile : %d, outfile : %d\n", ((t_cmd *)(cmd->content))->infile, ((t_cmd *)(cmd->content))->outfile);
		cmd = cmd->next;
	}
}

void    opening(t_list **cmd)
{
	t_cmd 	*content;
	t_list	*red;
	t_token *data;
	t_list  *lst;

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
					break;
			}
			else
			{
				if (!outfiling(content, data))
					break;
			}
			red = red->next;
		}
		lst = lst->next;
	}
	print_files(*cmd);
	return (pipex(cmd));
}