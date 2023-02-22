/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:43:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/22 22:28:15 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_lstdelone(t_token *lst)
{
	free(lst->value);
	free(lst);
}

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
		ft_lstdelone(head);
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

void	ft_envclear(t_env **list)
{
	t_env	*head;
	t_env	*body;

	if (!list || !(*list))
		return ;
	head = *list;
	while (head)
	{
		body = head->next;
		free(head->key);
		free(head->value);
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