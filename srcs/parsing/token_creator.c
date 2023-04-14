/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:53:35 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/14 23:34:11 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token	*data;

	data = malloc(sizeof(t_token));
	if (!data)
	{
		g_g.exit_malloc = 1;
		exit(12);
	}
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
		if (g_g.exit_malloc)
			cleaning_tkn(tab, t_lst);
		t_new = ft_lstnew(data);
		if (g_g.exit_malloc)
		{
			token_cleaner(data);
			cleaning_tkn(tab, t_lst);
		}
		t_lst = ft_lstadd_back(&t_lst, t_new);
	}
	free_tab(tab, -1);
	if (!t_lst)
		cleaning_tkn(tab, NULL);
	tokenisation(&t_lst);
	if (!parse_error(t_lst))
		return (ft_lstclear(&t_lst, token_cleaner));
	return (split_state(&t_lst));
}
