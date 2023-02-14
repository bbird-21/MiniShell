/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:33:36 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/13 20:33:21 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	what_red(char *str)
{
	if (ft_strnstr(str, "<<", 2))
		return (DROUT);
	else if (ft_strnstr(str, ">>", 2))
		return (DRIN);
	else if (ft_strnstr(str, "<", 1))
		return (RIN);
	else
		return (ROUT);
}

void	tokenisation(t_token **lst)
{
	t_token *previous;

	previous = NULL;
	while (*lst)
	{
		if (is_pipe((*lst)->value))
			(*lst)->type = PIPE;
		else if (is_red((*lst)->value))
			(*lst)->type = what_red((*lst)->value);
		else if (previous)
		{
			if (is_red(previous->value))
			{
				if (previous->type == 5)
					(*lst)->type = LIM;
				else
					(*lst)->type = FD;
			}
		}
		else
			(*lst)->type = WORD;
		previous = *lst;
		(*lst) = (*lst)->next;
	}
}