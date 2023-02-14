/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvina <alvina@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:31:58 by alvina            #+#    #+#             */
/*   Updated: 2023/02/11 18:47:58 by alvina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_space(char *str)
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

int	changing_state(char c, int state)
{
	if (c == 39)
	{
		if (state == 1)
			return (0);
		if (state == 0)
			return (1);
	}
	if (c == '"')
	{
		if (state == 2)
			return (0);
		if (state == 0)
			return (2);
	}
	return (state);
}

int is_separator(char *str)
{
	return (is_pipe(str) + is_red(str) + is_space(str));
}

int	count_words(char *str)
{
	int	i;
	int	nb;
	int	trigger;
	int state;

	i = 0;
	trigger = 0;
	nb = 0;
	state = 0;
	while (str[i])
	{
		state = changing_state(str[i], state);
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
		i++;
	}
	return (nb);
}