/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:18:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/20 20:09:22 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getsize(t_list *list)
{
	int		size;
	t_token	*data;
	
	data = (t_token *)(list->content);
	size = 0;
	while (list)
	{
		data = (t_token *)(list->content);
		size += ft_strlen(data->value);
		list = list->next;
	}
	return (size);
}

static void	join_token(t_list **list, char *new)
{
	t_list		*new_list;
	t_list		*new_node;
	t_token		*data;
	char		**split;
	int			i;
	
	i = 0;
	new_list = NULL;
	split = ft_split(new, ' ');
	while (split[i])
	{
		data = create_token(split[i]);
		if (!data)
		{
			free_tab(split, -1);
			ft_lstclear(&new_list, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
		new_node = ft_lstnew(data);
		if (!new_node)
		{
			free_tab(split, -1);
			ft_lstclear(&new_list, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
        new_list = ft_lstadd_back(&new_list, new_node);
		i++;
	}
	ft_lstclear(list, token_cleaner);
	(*list) = new_list;
}

void	tokjoin(t_list **list)
{
	char		*new;
	t_list		*tmp;
	t_token		*data;

	tmp = (*list);
	data = (t_token *)((*list)->content);
	new = NULL;
	new = malloc(sizeof(char) * getsize(*(list)) + 1);
	new[0] = '\0';
	while (tmp)
	{
		data = (t_token *)(tmp->content);
		new = ft_strjoin(new, data->value);
		tmp = tmp->next;
	}
	join_token(list, new);
}
