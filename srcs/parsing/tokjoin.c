/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 21:18:56 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/04/06 23:10:12 by mmeguedm         ###   ########.fr       */
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

void	split_token(t_list **list, char *new)
{
	t_list	*new_list;
	t_list	*new_node;
	t_token	*data;
	char	**split;
	int		i;

	i = 0;
	new_list = NULL;
	split = ft_split(new, ' ');
	free(new);
	while (split[i])
	{
		data = create_token(split[i]);
		if (!data)
			cleaning_tkn(split, new_list);
		new_node = ft_lstnew(data);
		if (!new_node)
			cleaning_tkn(split, new_list);
		new_list = ft_lstadd_back(&new_list, new_node);
		i++;
	}
	free_tab(split, -1);
	ft_lstclear(list, token_cleaner);
	(*list) = new_list;
}

void	one_token_treatment(t_list **list)
{
	t_token	*data;
	char	*new;

	data = (t_token *)((*list)->content);
	if (data->type == WORD || data->type == FD)
	{
		new = ft_strdup(((t_token *)((*list)->content))->value);
		if (new && new[0] != '\0')
			split_token(list, new);
		else
			free(new);
	}
}

void	tokjoin(t_list **list, int j)
{
	char	*new;
	t_list	*tmp;
	t_token	*data;

	if (j > 1)
	{
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
		split_token(list, new);
	}
	else
		one_token_treatment(list);
}
