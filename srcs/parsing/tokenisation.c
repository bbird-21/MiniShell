/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:33:36 by ale-sain          #+#    #+#             */
/*   Updated: 2023/03/29 10:02:20 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	what_red(char *str)
{
	if (ft_strnstr(str, ">>", 2))
		return (DROUT);
	else if (ft_strnstr(str, "<<", 2))
		return (DRIN);
	else if (ft_strnstr(str, "<", 1))
		return (RIN);
	else
		return (ROUT);
}
static void	type_red(t_token *c_data, t_list *previous)
{
	if (is_red(((t_token*)(previous->content))->value) && !is_separator(c_data->value))
	{
		if (c_data->type == 5)
			c_data->type = LIM;
		else
			c_data->type = FD;
	}
}
void	tokenisation(t_list **lst)
{
	t_list *previous;
	t_list	*curr;
	t_token	*c_data;

	previous = NULL;
	curr = *lst;
	while (curr)
	{
		c_data = (t_token*)(curr->content);
		if (is_pipe(c_data->value))
			c_data->type = PIPE;
		else if (is_red(c_data->value))
			c_data->type = what_red(c_data->value);
		else if (previous)
			type_red(c_data, previous);
		else
			c_data->type = WORD;
		previous = curr;
		curr = curr->next;
	}
}