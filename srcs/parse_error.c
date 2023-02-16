/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:41 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/15 17:53:40 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_tokenisation(t_token **lst)
{
	t_token *previous;

	previous = NULL;
	while (*lst)
	{
		if (is_pipe((*lst)->value))
			(*lst)->type = PIPE;
		else if (is_red((*lst)->value))
			(*lst)->type = what_red((*lst)->value);
		else
			(*lst)->type = WORD;
		(*lst) = (*lst)->next;
	}
}