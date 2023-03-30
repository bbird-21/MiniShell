/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:41:18 by alvina            #+#    #+#             */
/*   Updated: 2023/03/30 11:41:39 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reverse_magic_space(t_list **arg)
{
	t_list	*tmp;
	t_token	*content;
	int		i;

	tmp = *arg;
	i = 0;
	while (*arg)
	{
		content = (t_token *)(*arg)->content;
		if (content->value)
		{
			while (content->value[i])
			{
				if (content->value[i] == -32)
					content->value[i] = ' ';
				i++;
			}
		}
		(*arg) = (*arg)->next;
		i = 0;
	}
	*arg = tmp;
}

void	cleaning_cmd(t_list **token, t_list **cmd)
{
	ft_lstclear(token, token_cleaner);
	ft_lstclear(cmd, cmd_cleaner);
	handler(4, NULL, NULL);
	exit(1);
}
