/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:51:42 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/29 13:04:36 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*arg_red_list(t_list **arg_red, int type, char *str)
{
	t_token	*data;
	t_list	*new;

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

t_cmd	*initializing_data(void)
{
	t_cmd	*data;

	data = malloc(sizeof(t_cmd));
	if (!data)
		return (NULL);
	data->arg = NULL;
	data->red = NULL;
	data->infile = -2;
	data->outfile = -2;
	data->pfd[0] = 0;
	data->pfd[1] = 0;
	return (data);
}

int	cmd_core(t_list **token, t_cmd *data, t_token *content, int *flag)
{
	if (content->type == WORD)
	{
		data->arg = arg_red_list(&data->arg, 0, content->value);
		if (!data->arg)
			return (cmd_cleaner(data), 0);
	}
	else
	{
		data->red = arg_red_list(&data->red, content->type,
				((t_token *)((*token)->next->content))->value);
		if (!data->red)
			return (cmd_cleaner(data), 0);
		(*token) = (*token)->next;
		(*flag)++;
	}
	return (1);
}

t_cmd	*data_cmd(t_list *token, int *flag)
{
	t_cmd	*data;
	t_token	*content;

	*flag = 1;
	data = initializing_data();
	if (!data)
		return (NULL);
	while (token)
	{
		content = (t_token *)token->content;
		if (content->type == PIPE)
			break ;
		if (!cmd_core(&token, data, content, flag))
			return (NULL);
		token = token->next;
		(*flag)++;
	}
	if (!token)
		*flag = 0;
	return (data);
}

void	reverse_magic_space(t_list **arg)
{
	t_list	*tmp;
	t_token	*content;
	int		i;

	tmp = *arg;
	i = 0;
	while (*arg)
	{
		content = (t_token *)(*arg)->content;
		if (content->value)
		{
			while (content->value[i])
			{
				if (content->value[i] == -32)
					content->value[i] = ' ';
				i++;
			}
		}
		(*arg) = (*arg)->next;
		i = 0;
	}
	*arg = tmp;
}

void	cleaning_cmd(t_list **token, t_list **cmd)
{
	ft_lstclear(token, token_cleaner);
	ft_lstclear(cmd, cmd_cleaner);
	handler(4, NULL, NULL);
	exit(1);
}

void	cmd_generator(t_list **token)
{
	int		i;
	int		flag;
	t_list 	*list_cmd;
	t_list 	*new_cmd;
	t_cmd	*data;
	t_list	*head;

	list_cmd = NULL;
	flag = 1;
	i = -1;
	head = *token;
	while (flag)
	{
		data = data_cmd(*token, &flag);
		if (!data)
			cleaning_cmd(&head, &list_cmd);
		new_cmd = ft_lstnew(data);
		list_cmd = ft_lstadd_back(&list_cmd, new_cmd);
		while ((++i < flag) && (*token))
			(*token) = (*token)->next;
		i = -1;
	}
	ft_lstclear(&head, token_cleaner);
	reverse_magic_space(&((t_cmd *)(list_cmd->content))->arg);
	// print_lst(list_cmd, print_cmd);
	return (here_doc(&list_cmd));
}

	// return (here_doc(&list_cmd));