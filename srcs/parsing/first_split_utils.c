/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:31:58 by alvina            #+#    #+#             */
/*   Updated: 2023/03/30 11:35:54 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i])
	{
		if (str[i] == ' ')
		{
			i += is_space(&str[i + 1]);
			i++;
		}
	}
	return (i);
}

int	is_red(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			i += is_red(&str[i + 1]);
			i++;
		}
	}
	return (i);
}

int	is_pipe(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i])
	{
		if (str[i] == '|')
		{
			i += is_pipe(&str[i + 1]);
			i++;
		}
	}
	return (i);
}

int	is_separator(char *str)
{
	return (is_pipe(str) + is_red(str) + is_space(str));
}

int	count_words(char *str, int i)
{
	int	nb;
	int	trigger;
	int	state;

	trigger = 0;
	nb = 0;
	while (str[++i])
	{
		state = changing_state(str[i]);
		if (state == 0 && is_separator(&str[i]))
		{
			if (!is_space(&str[i]))
				nb++;
			i += (is_separator(&str[i]) - 1);
			trigger = 0;
		}
		else if (((!is_space(&str[i])) || state != 0) && trigger == 0)
		{
			trigger = 1;
			nb++;
		}
	}
	return (changing_state((char)-1), nb);
}
