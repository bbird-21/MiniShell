/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:51:42 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 20:20:41 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_arg(t_token **arg, char *str)
{
	t_token		*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return ;
    new->value = ft_strdup(str);
    new->type = 0;
    new->next = NULL;
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
	token_add_back(red, new);
}

t_cmd   *new_cmd(t_cmd **cmd, t_token **list)
{
    t_cmd   *new;
    t_token *lst;

    lst = *list;
    new = malloc(sizeof(t_cmd));
    new->arg = NULL;
    new->red = NULL;
	if (!new)
		return (NULL);
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
        }
        lst = lst->next;
    }
    new->infile = 0;
    new->outfile = 0;
	new->next = NULL;
    return (cmd_add_back(cmd, new));
}

void    cmd_generator(t_token **lst)
{
	t_cmd   *cmd;

	cmd = NULL;
	while (*lst)
	{
        if (!new_cmd(&cmd, lst))
		{
			ft_lstclear(lst);
			ft_cmdclear(&cmd);
			return ;
		}
        (*lst) = (*lst)->next;
	}
    ft_lstclear(lst);
	return (print_cmd(cmd));
}