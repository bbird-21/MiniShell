/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:43:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/23 10:25:21 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	token_cleaner(void *content)
{
	free(((t_token*)content)->value);
	free((t_token*)content);
}

void	env_cleaner(void *content)
{
	t_env	*data;

	data = (t_env*)content;
	free(data->key);
	free(data->value);
	free(data);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*body;

	if (!lst || !(*del) || !(*lst))
		return ;
	head = (*lst);
	while (head)
	{
		body = head->next;
		del(head->content);
		free(head);
		head = body;
	}
	(*lst) = NULL;
}

// void	ft_cmdclear(t_cmd **lst)
// {
// 	t_cmd	*head;
// 	t_cmd	*body;

// 	if (!lst || !(*lst))
// 		return ;
// 	head = *lst;
// 	while (head)
// 	{
// 		body = head->next;
// 		ft_lstclear(&(head->arg));
// 		ft_lstclear(&(head->red));
// 		free(head);
// 		head = body;
// 	}
// }

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