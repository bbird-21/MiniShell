/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:41:18 by alvina            #+#    #+#             */
/*   Updated: 2023/04/24 19:11:46 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	looping(t_list **list)
{
	t_list	*lst;

	lst = *list;
	while (lst)
	{
		reverse_magic_space(&((t_cmd *)(lst->content))->arg);
		lst = lst->next;
	}
}

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

void	cleaning_cmd(t_cmd *data, t_list **token, t_list **cmd)
{
	if (data)
		free(data);
	ft_lstclear(token, token_cleaner);
	ft_lstclear(cmd, cmd_cleaner);
	handler(4, NULL, NULL);
	exit_malloc();
}

char	*home_prt(void)
{
	char	*new;

	new = ft_getenv("HOME");
	if (!new)
		ft_putstr_fd("cd : home not set\n", 2);
	return (new);
}
