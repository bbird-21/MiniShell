/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:53:35 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/17 16:16:31 by alvina           ###   ########.fr       */
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

void	token_generator(char **tab)
{
	int		i;
	t_token *data;
	t_list	*t_new;
	t_list	*t_lst;

	i = 0;
	t_lst = NULL;
	while (tab[i])
	{
		data = create_token(tab[i]);
		if (!data)
		{
			free_tab(tab, -1);
			ft_lstclear(&t_lst, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
        t_new = ft_lstnew(data);
		if (!t_new)
		{
			free_tab(tab, -1);
			ft_lstclear(&t_lst, token_cleaner);
			handler(4, NULL, NULL);
			exit(0);
		}
        t_lst = ft_lstadd_back(&t_lst, t_new);
		i++;
	}
	free_tab(tab, -1);
	if (!t_lst)
	{
		handler(4, NULL, NULL);
		exit(0);
	}
	tokenisation(&t_lst);
	if (!parse_error(t_lst))
	{
		ft_lstclear(&t_lst, token_cleaner);
		handler(4, NULL, NULL);
		return ;
	}
	return (split_state(&t_lst));
	// return (expansion(t_lst));
	// return (cmd_generator(&t_lst));
}