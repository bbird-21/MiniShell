/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inutils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:44:43 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/23 14:36:32 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (!lst)
		return ;
	while (lst)
	{
		print(lst->content);
		lst = lst->next;
	}
	printf("\n");
}