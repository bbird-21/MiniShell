/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:43 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/18 14:57:32 by ale-sain         ###   ########.fr       */
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
		if (lst->type != WORD)
			printf("%d ", lst->type);
		lst = lst->next;
	}
}

void	print_cmd(t_cmd *cmd)
{
	int	i = 0;

	while (cmd)
	{
		printf("\nCommande %d", i);
		printf("\nARG : ");
		print_lst(cmd->arg);
		printf("\nRED : ");
    	print_lst(cmd->red);
		cmd = cmd->next;
		i++;
	}
	printf("\n");
}