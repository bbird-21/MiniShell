/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:32:27 by mmeguedm          #+#    #+#             */
/*   Updated: 2023/03/17 19:49:40 by alvina           ###   ########.fr       */
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
	if (!lst)
		return ;
	while (lst)
	{
		print(lst->content);
		lst = lst->next;
	}
	printf("\n");
}

char	*trans_env(void *content)
{
	t_env *data;
	char	*tmp;
	char	*new;

	data = (t_env *)content;
	tmp = simple_join(data->key, "=");
	new = simple_join(tmp, data->value);
	free(tmp);
	return (new);
}

char	*trans_token(void *content)
{
	t_token	*data;

	data = (t_token *)content;
	return (ft_strdup(data->value));
}

/* How to use translator ? 
		To generate double tab of ARG from t_cmd :
				t_cmd *cont = (t_cmd *)list_cmd->content;
				char **tab = translator(cont->arg, trans_token);
		To generate double tab of ENV :
				char **tab = translator(handler(5, NULL, NULL), trans_env); */
char	**translator(t_list *lst, char *(translate)(void *))
{
	t_list *head;
	int		i;
	char	**tab;

	i = 0;
	head = lst;
	if (!lst)
		return (NULL);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	lst = head;
	tab = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (lst)
	{
		tab[i] = translate(lst->content);
		lst = lst->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
