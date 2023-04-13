/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:03:01 by alvina            #+#    #+#             */
/*   Updated: 2023/04/13 14:14:12 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(void *content)
{
	t_token	*data;

	data = (t_token *)content;
	if (data->value)
		printf("value = %s \n", data->value);
	if (data->type)
		printf("%d \n", data->type);
}

void	print_env(void *content)
{
	t_env	*data;

	data = (t_env *)content;
	printf("%s=", data->key);
	printf("%s \n", data->value);
}

void	print_cmd(void *content)
{
	t_cmd	*data;

	data = (t_cmd *)content;
	printf("\n---COMMANDE---\n");
	printf("\nARG : ");
	print_lst(data->arg, print_token);
	printf("\nRED :");
	print_lst(data->red, print_token);
}

void	print_lst(t_list *lst, void (*print)(void *))
{
	if (!lst)
		return ;
	while (lst)
	{
		print(lst->content);
		lst = lst->next;
	}
}
