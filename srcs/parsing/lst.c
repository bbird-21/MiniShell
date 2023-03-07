/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:32:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/07 18:21:03 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_node_back_token(t_list **l, char *str, int *index, int type)
{
	t_token	*data;
	t_list	*new;

	data = malloc(sizeof(*data));
	new = malloc(sizeof(*new));
	if (!data || !new)
		return (ft_lstclear(l, token_cleaner), free_exit(NULL));
	data->value = get_token(str, index);
	data->type = type;
	new->content = data;
	new->next = NULL;
	ft_lstadd_back(l, new);
}

void	print_token(void *content)
{
	t_token *data;

	data = (t_token *)content;
	printf("%s ", data->value);
	printf("%d \n", data->type);
}

void	print_env(void *content)
{
	t_env *data;

	data = (t_env *)content;
	printf("%s=", data->key);
	printf("%s \n", data->value);
}

void	print_cmd(void *content)
{
	t_cmd *data;
	
	data = (t_cmd *)content;
	printf("\n---COMMANDE---\n");
	printf("\nARG : ");
	print_lst(data->arg, print_token);
	printf("\nRED : ");
	print_lst(data->red, print_token);
}

void	print_lst(t_list *lst, void (*print)(void *))
{
	int	count;

	count = 0;
	if (!lst)
		return ;
	while (lst)
	{
		print(lst->content);
		lst = lst->next;
	}
	printf("\n");
}
