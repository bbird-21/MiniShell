/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeguedm <mmeguedm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:51:42 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/07 20:08:24 by mmeguedm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_list	*arg_red_list(t_list **arg_red, int type, char *str)
{
	t_token *data;
    t_list  *new;

    data = create_token(str);
	if (!data)
        return (NULL);
    data->type = type;
    new = ft_lstnew(data);
    if (!new)
	{
		ft_lstclear(arg_red, token_cleaner);
		return (NULL);
	}
    return (ft_lstadd_back(arg_red, new));
}

t_cmd   *initializing_data(void)
{
    t_cmd   *data;
    
    data = malloc(sizeof(t_cmd));
    if (!data)
        return (NULL);
    data->arg = NULL;
    data->red = NULL;
    data->infile = 0;
    data->outfile = 0;
    return (data);
}

t_cmd   *data_cmd(t_list *token, int *flag)
{
    t_cmd   *data;
    t_token *content;

    *flag = 1;
    data = initializing_data();
    if (!data)
            return (NULL);
	while (token)
    {
        content = (t_token *)token->content;
        if (content->type == PIPE)
            break;
        if (content->type == WORD)
        {
            data->arg = arg_red_list(&data->arg, 0, content->value);
            if (!data->arg)
                return (cmd_cleaner(data), NULL);
        }
        else
        {
            data->red = arg_red_list(&data->red, content->type, ((t_token*)(token->next->content))->value);
            if (!data->red)
                return (cmd_cleaner(data), NULL);
            token = token->next;
            (*flag)++;
        }
        token = token->next;
        (*flag)++;
    }
    if (!token)
        *flag = 0;
    return (data);
}

void    cmd_generator(t_list **token)
{
	t_list  *list_cmd;
    t_list  *new_cmd;
    t_cmd   *data;
    int     i;
    int     flag;
    t_list *head;

	list_cmd = NULL;
    flag = 1;
    i = -1;
    head = *token;
	while (flag)
	{
        data = data_cmd(*token, &flag);
        if (!data)
		{
			ft_lstclear(&head, token_cleaner);
			ft_lstclear(&list_cmd, cmd_cleaner);
            handler(4, NULL, NULL);
			exit(1);
		}
        new_cmd = ft_lstnew(data);
        list_cmd = ft_lstadd_back(&list_cmd, new_cmd);
        while ((++i < flag) && (*token))
            (*token) = (*token)->next;
        i = -1;
	}
    ft_lstclear(&head, token_cleaner);
    print_lst(list_cmd, print_cmd);
    ft_lstclear(&list_cmd, cmd_cleaner);
    return ;
}