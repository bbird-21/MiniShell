/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:51:42 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/18 19:13:15 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cmd_arg(t_token **arg, char *str)
{
	t_token		*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
    new->value = ft_strdup(str);
    new->type = 0;
    new->next = NULL;
    if (!new->value)
	{
		free(new);
		return ;
	}
	token_add_back(arg, new);
}
    
void    cmd_red(t_token **red, int type, char *file)
{
    t_token		*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
    new->value = ft_strdup(file);
    new->type = type;
    new->next = NULL;
    if (!new->value)
	{
		free(new);
		return ;
	}
	token_add_back(red, new);
}

int new_cmd(t_cmd **cmd, t_token **list)
{
    t_cmd   *new;
    t_token *lst;
    int     i;

    i = 0;
    lst = *list;
    new = malloc(sizeof(t_cmd));
    new->arg = NULL;
    new->red = NULL;
	if (!new)
		return (-1);
	while (lst)
    {
        if (lst->type == PIPE)
            break;
        if (lst->type == WORD)
            cmd_arg(&(new->arg), lst->value);
        else
        {
            cmd_red(&(new->red), lst->type, lst->next->value);
            lst = lst->next;
            i++;
        }
        lst = lst->next;
        i++;
    }
    new->infile = 0;
    new->outfile = 0;
	new->next = NULL;
    cmd_add_back(cmd, new);
    if (!lst)
        return (0);
    return (i + 1);
}

void    cmd_generator(t_token **lst)
{
	t_cmd   *cmd;
    int     i;
    int     flag;
    t_token *head;

	cmd = NULL;
    flag = 1;
    i = 0;
    head = *lst;
	while (flag)
	{
        flag = new_cmd(&cmd, lst);
        if (flag == -1)
		{
			ft_lstclear(&head);
			ft_cmdclear(&cmd);
			return ;
		}
        while (i < flag && (*lst))
        {
            (*lst) = (*lst)->next;
            i++;
        }
        i = 0;
	}
    ft_lstclear(&head);
	print_cmd(cmd);
    ft_cmdclear(&cmd);
}