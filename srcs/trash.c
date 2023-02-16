/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:43:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 18:06:51 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear(t_token **list)
{
	t_token	*head;
	t_token	*body;

	if (!list || !(*list))
		return ;
	head = *list;
	while (head)
	{
		body = head->next;
		free(head);
		head = body;
	}
}

void	ft_cmdclear(t_cmd **lst)
{
	t_cmd	*head;
	t_cmd	*body;

	if (!lst || !(*lst))
		return ;
	head = *lst;
	while (head)
	{
		body = head->next;
		ft_lstclear(&(head->arg));
		ft_lstclear(&(head->red));
		free(head);
		head = body;
	}
}

char	**free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	if (j == -1)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	else
	{
		while (i < j)
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
	return (NULL);
}