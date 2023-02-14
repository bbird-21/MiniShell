/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:42:29 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/14 15:57:43 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*generator_token(t_token **lst, char *str)
{
	t_token		*new;

	new = ft_lstnew(str);
	if (!new)
		return (NULL);
	return (ft_lstadd_back(lst, new));
}

t_token	*generator(char **tab)
{
	int	i;
	t_token *lst;
	t_token *head;

	i = 0;
	lst = NULL;
	while (tab[i])
	{
		if (!generator_token(&lst, tab[i]))
		{
			if (!lst)
				return (0);
			ft_lstclear(&head);
			return (0);
		}
		if (i == 0)
			head = lst;
		i++;
	}
	return (head);
}

void	minishell(char *str)
{
	char **tab;
	t_token *lst;
	t_token *head;

	tab = first_split(str);
	if (!tab)
	{
		free(str);
		get_next_line(0, 1);
		exit(0);
	}
	lst = generator(tab);
	head = lst;
	tokenisation(&lst);
	print_lst(head);
	free_tab(tab, -1);
    free(str);
    ft_lstclear(&head);
}

int main()
{
	char	*str;

	while (1)
	{
        str = readline("nanoshell > ");
		if (!str)
			break;
		minishell(str);
	}
}