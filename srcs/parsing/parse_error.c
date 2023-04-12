/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:41 by ale-sain          #+#    #+#             */
/*   Updated: 2023/04/12 17:13:44 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// si rien aprs pipe : error parse? ou ouverture entree standard? + +eurs pipes
int	parse_pipe(t_list *previous, t_token *curr_data, t_list *next)
{
	if (!previous || !next)
		return (error_msg(curr_data->value));
	if (ft_strlen(curr_data->value) > 1)
		return (error_msg(&curr_data->value[1]));
	return (1);
}

// parsing si apres !fd / lim / rien, si + de 2 carac etc
int	parse_red(t_token *curr_data, t_list *next)
{
	t_token	*next_data;

	if (ft_strlen(curr_data->value) >= 2)
	{
		if (curr_data->value[0] != curr_data->value[1])
			return (error_msg(&curr_data->value[1]));
		else if (ft_strlen(curr_data->value) > 2)
			return (error_msg(&curr_data->value[2]));
	}
	if (!next)
		return (error_msg("newline"));
	next_data = (t_token *)(next->content);
	if (next_data->type != FD && next_data->type != LIM)
		return (error_msg(next_data->value));
	return (1);
}

int	parse_quote(char *str)
{
	int	i;
	int	state;

	i = 0;
	state = changing_state((char)-1);
	while (str[i])
	{
		state = changing_state(str[i]);
		i++;
	}
	if (state != 0)
	{
		ft_putendl_fd("nanoshell: syntax error : quote unclosed", 2);
		return (0);
	}
	return (1);
}

int	parse_other_than_pipe(t_list *lst, t_token *lst_data)
{
	if (lst_data->type == RIN || lst_data->type == DRIN
		|| lst_data->type == ROUT || lst_data->type == DROUT)
	{
		if (!parse_red(lst_data, lst->next))
			return (0);
	}
	return (1);
}

int	parse_error(t_list *lst)
{
	t_list	*previous;
	t_token	*lst_data;

	previous = NULL;
	if (!lst)
		return (0);
	while (lst)
	{
		lst_data = (t_token *)(lst->content);
		if (lst_data->type == PIPE)
		{
			if (!parse_pipe(previous, lst_data, lst->next))
				return (ft_lstclear(&lst, token_cleaner), 0);
		}
		else if (!parse_other_than_pipe(lst, lst_data))
			return (ft_lstclear(&lst, token_cleaner), 0);
		previous = lst;
		lst = lst->next;
	}
	return (1);
}
