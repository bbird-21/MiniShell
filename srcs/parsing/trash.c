/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:43:34 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/24 18:51:13 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cmd_cleaner(void *content)
{
	t_cmd *data;

	data = (t_cmd*)content;
	ft_lstclear(&data->arg, token_cleaner);
	ft_lstclear(&data->red, token_cleaner);
	free(data);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*body;

	if (!lst || !(*lst))
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

char	**free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	if (j == -1)
	{
		if (tab[i])
		{
			while (tab[i])
			{
				free(tab[i]);
				i++;
			}
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