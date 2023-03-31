/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:53:35 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/31 10:18:04 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token	*data;

	data = malloc(sizeof(t_token));
	if (!data)
		return (NULL);
	data->value = ft_strdup(str);
	if (!data->value)
	{
		free(data);
		return (NULL);
	}
	data->type = 0;
	return (data);
}

void	cleaning_tkn(char **tab, t_list *lst)
{
	free_tab(tab, -1);
	if (lst)
		ft_lstclear(&lst, token_cleaner);
	exit_malloc();
}

void	token_generator(char **tab, int i)
{
	t_token	*data;
	t_list	*t_new;
	t_list	*t_lst;

	t_lst = NULL;
	while (tab[++i])
	{
		data = create_token(tab[i]);
		if (!data)
			cleaning_tkn(tab, t_lst);
		t_new = ft_lstnew(data);
		if (!t_new)
			cleaning_tkn(tab, t_lst);
		t_lst = ft_lstadd_back(&t_lst, t_new);
	}
	free_tab(tab, -1);
	if (!t_lst)
		cleaning_tkn(tab, NULL);
	tokenisation(&t_lst);
	if (!parse_error(t_lst))
	{
		ft_lstclear(&t_lst, token_cleaner);
		return ;
	}
	return (split_state(&t_lst));
}
