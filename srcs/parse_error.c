/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:44:41 by ale-sain          #+#    #+#             */
/*   Updated: 2023/02/16 14:34:04 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_msg(char *value)
{
	ft_putstr_fd("nanoshell: syntax error near unexpected token : ", 2);
	ft_putendl_fd(value, 2);
	return (0);
}

// si rien aprs pipe : error parse? ou ouverture entree standard? + +eurs pipes
int	parse_pipe(t_token *previous, t_token *curr, t_token *next)
{
	if (!previous || !next)
		return (error_msg(curr->value));
	if (ft_strlen(curr->value) > 2)
		return (error_msg(&curr->value[2]));
	return (1);
}

// parsing si apres !fd / lim / rien, si + de 2 carac etc
int	parse_red(t_token *curr, t_token *next)
{
	if (!next)
		return (error_msg("newline"));
	
	if (ft_strlen(curr->value) >= 2)
	{
		if (curr->value[0] != curr->value[1])
			return (error_msg(&curr->value[1]));
		else if (ft_strlen(curr->value) > 2)
			return (error_msg(&curr->value[2]));
	}
	if (next->type != FD && next->type != LIM)
		return (error_msg(next->value));
	return (1);
}

int	parse_quote(char *str)
{
	int	i;
	int state;

	i = 0;
	state = 0;
	while (str[i])
	{
		state = changing_state(str[i], state);
		i++;
	}
	if (state != 0)
	{
		ft_putendl_fd("nanoshell: syntax error : quote unclosed", 2);
		return (0);
	}
	return (1);
}

int	parse_error(t_token *lst)
{
	t_token *previous;

	previous = NULL;
	if (!lst)
		return (0);
	while (lst)
	{
		if (lst->type == PIPE)
		{
			if (!parse_pipe(previous, lst, lst->next))
				return (0);
		}
		else if (lst->type == RIN || lst->type == DRIN
			|| lst->type == ROUT || lst->type == DROUT)
		{
			if (!parse_red(lst, lst->next))
				return (0);
		}
		else if (lst->type == WORD || lst->type == FD || lst->type == LIM)
		{
			if (!parse_quote(lst->value))
				return (0);
		}
		previous = lst;
		lst = lst->next;
	}
	return (1);
}
