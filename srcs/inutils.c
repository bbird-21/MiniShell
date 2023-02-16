/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:43 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 20:28:27 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst(t_token *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("%s ", lst->value);
		printf("%d\n", lst->type);
		lst = lst->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	t_cmd *head = cmd;
	while (cmd)
	{
		while (cmd->arg)
		{
			printf("%s ", cmd->arg->value);
			cmd->arg = cmd->arg->next;
		}
		printf("\n");
		while (cmd->red)
		{
			printf("%d : %s / ", head->red->type, head->red->value);
			cmd->red = cmd->red->next;
		}
		cmd = cmd->next;
	}
	ft_cmdclear(&cmd);
}