/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:33:36 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 10:03:48 by ale-sain         ###   ########.fr       */
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
	t_token	*bl;

	previous = NULL;
	bl = *lst;
	while (bl)
	{
		if (is_pipe(bl->value))
			bl->type = PIPE;
		else if (is_red(bl->value))
			bl->type = what_red(bl->value);
		else if (previous)
		{
			if (is_red(previous->value) && !is_separator((bl->value)))
			{
				if (previous->type == 5)
					bl->type = LIM;
				else
					bl->type = FD;
			}
		}
		else
			bl->type = WORD;
		previous = bl;
		bl = bl->next;
	}
}